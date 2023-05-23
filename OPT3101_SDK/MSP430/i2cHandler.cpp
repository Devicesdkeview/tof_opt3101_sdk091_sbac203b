/*
 * i2cHandler.cpp
 *
 *  Created on: Nov 19, 2017
 *	  Author: a0875461
 */

#include "i2cHandler.h"
#include "../definitions.h"

#include "../hostController.h"

I2C::i2cHandler::i2cHandler(void){
#ifdef TIMSP430F5529_LAUNCHPAD_CALIBRATION_TOOL
	this->slaveAddress=OPT3101_I2C_SLAVEADDRESS;
#endif
	this->regBankSize=3;
	this->timeOut=0xFF;
	this->dataRx= new uint8_t[this->regBankSize+1];
	this->continousReadByteCount=3*3-1;
	this->continousReadRegisterAddress=0x08;
}

I2C::i2cHandler::~i2cHandler(void){
	delete [] this->dataRx;
	this->dataRx=NULL;
}

void I2C::i2cHandler::init(void){
	this->i2cParam.selectClockSource = USCI_B_I2C_CLOCKSOURCE_SMCLK; // Clecting the SMCLK For the I2C Clocks.
	this->i2cParam.i2cClk = UCS_getSMCLK();
	this->i2cParam.dataRate = USCI_B_I2C_SET_DATA_RATE_400KBPS; // Setting to 400KBPS
	USCI_B_I2C_initMaster(USCI_B1_BASE, &this->i2cParam);

	//Specify slave address
	USCI_B_I2C_setSlaveAddress(USCI_B1_BASE,this->slaveAddress);
	this->slaveAddress_=this->slaveAddress;

	//Set Transmit mode
	//USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_TRANSMIT_MODE); // Setting device as I2C Master device.

	//Enable I2C Module to start operations
	USCI_B_I2C_enable(USCI_B1_BASE); // Enabling the I2C Module

}

void I2C::i2cHandler::updateSlaveAddress(){
	if(this->slaveAddress_!=this->slaveAddress){
		this->slaveAddress_=this->slaveAddress;
		USCI_B_I2C_setSlaveAddress(USCI_B1_BASE,this->slaveAddress);
	}
}

bool I2C::i2cHandler::write(){
	static uint32_t cnt;
	static uint8_t c;
	static bool state;

	this->updateSlaveAddress();
	state=true;
    USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_TRANSMIT_MODE);

    cnt=this->timeOut;
	while((USCI_B_I2C_isBusBusy(USCI_B1_BASE)) & cnt--);
	if(!cnt)
		return false;
	state&=USCI_B_I2C_masterSendMultiByteStartWithTimeout(USCI_B1_BASE,this->address,this->timeOut); // Function returns 1 for success
	if(!state)
		return false;

	while (USCI_B_I2C_masterIsStartSent(USCI_B1_BASE));
	for(c=0;c<this->regBankSize;c++)
		state&=USCI_B_I2C_masterSendMultiByteNextWithTimeout(USCI_B1_BASE,this->dataTx[c],this->timeOut);
	state&=USCI_B_I2C_masterSendMultiByteStopWithTimeout(USCI_B1_BASE,this->timeOut); // Function returns 1 for success
	while (USCI_B_I2C_masterIsStopSent(USCI_B1_BASE));
    USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_TRANSMIT_MODE);
	return state;
}


bool I2C::i2cHandler::write(uint8_t address,uint8_t *data){
	this->address=address;
	this->dataTx=data;
	return this->write();
}
/* This is overloaded function of i2C Write. This makes the register interface simple */
bool I2C::i2cHandler::write(uint8_t address,uint32_t data){
	this->address=address;
	this->dataTx=(uint8_t*) &data;
	return this->write();
}
/* This is overloaded function of i2C Write. This makes the register interface simple */
bool I2C::i2cHandler::write(uint8_t *data){
	this->address=data[0];
	this->dataTx=&data[1];
	return this->write();
}

bool I2C::i2cHandler::read(){
	static bool state;
	static uint8_t c;
	static uint32_t cnt;
	this->updateSlaveAddress();
	state=true;
	cnt=this->timeOut;
	while((USCI_B_I2C_isBusBusy(USCI_B1_BASE)) & cnt--);
	if(!cnt)
		return false;
	state&=USCI_B_I2C_masterSendSingleByteWithTimeout(USCI_B1_BASE,this->dataRx[0],this->timeOut); // Function returns 1 for success
	if(!state)
		return false;
	cnt=this->timeOut;
	while (USCI_B_I2C_masterIsStartSent(USCI_B1_BASE) & cnt--);
	if(!cnt)
		return false;
	USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_RECEIVE_MODE);
	USCI_B_I2C_masterReceiveMultiByteStart(USCI_B1_BASE);
	for(c=1;c<this->regBankSize;c++)
		this->dataRx[c]=USCI_B_I2C_masterReceiveSingle(USCI_B1_BASE);
	USCI_B_I2C_masterReceiveMultiByteStop(USCI_B1_BASE);
	this->dataRx[c]=USCI_B_I2C_masterReceiveMultiByteEndPoll(USCI_B1_BASE);
    USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_TRANSMIT_MODE);
	return state;
}

bool I2C::i2cHandler::continuousRead(uint8_t *data){
	static bool state;
	static uint8_t c;

	state=true;
	if(USCI_B_I2C_isBusBusy(USCI_B1_BASE))
		return false;
	state&=USCI_B_I2C_masterSendSingleByteWithTimeout(USCI_B1_BASE,this->continousReadRegisterAddress,this->timeOut); // Function returns 1 for success
	while (USCI_B_I2C_masterIsStartSent(USCI_B1_BASE));
    USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_RECEIVE_MODE);
	USCI_B_I2C_masterReceiveMultiByteStart(USCI_B1_BASE);
	for(c=0;c<this->continousReadByteCount;c++)
		data[c]=USCI_B_I2C_masterReceiveSingle(USCI_B1_BASE);
    USCI_B_I2C_masterReceiveMultiByteStop(USCI_B1_BASE);
	data[c]=USCI_B_I2C_masterReceiveMultiByteEndPoll(USCI_B1_BASE);
    USCI_B_I2C_setMode(USCI_B1_BASE,USCI_B_I2C_TRANSMIT_MODE);
	return state;
}




uint8_t* I2C::i2cHandler::read(uint8_t address){
	this->dataRx[0]=address;
	this->read();
	return &this->dataRx[1];
}

bool I2C::i2cHandler::read(uint8_t address,uint8_t *data){
	static bool state;
	static uint8_t c;

	this->dataRx[0]=address;
	state=this->read();
	for(c=1;c<this->regBankSize+1;c++)
		data[c-1]=this->dataRx[c];
	return state;
}

bool I2C::i2cHandler::read(uint8_t *data){
	static bool state;
	static uint8_t c;
	state=true;
	this->dataRx[0]=data[0];
	state=this->read();
	for(c=1;c<this->regBankSize+1;c++)
		data[c]=this->dataRx[c];
	return state;
}

bool I2C::i2cHandler::read(uint8_t address,uint32_t *data){
	static bool state;
	static uint8_t c;
	static uint32_t addon;
	state=true;

	this->dataRx[0]=address;
	state=this->read();
	*data=0;
	for(c=0;c<this->regBankSize;c++){
	    addon=this->dataRx[1+c];
	    addon=addon<<(c<<3);
	    *data+=addon;
	}

	return state;
}

