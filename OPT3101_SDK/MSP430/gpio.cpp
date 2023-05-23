/*
 * portAssign.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: a0875461
 */
#include <MSP430/gpio.h>

void GPIO::gpio::operator=(uint8_t value){
	this->setAsOutputPin();
	if(value){
		GPIO_setOutputHighOnPin(this->port,this->pin);
		this->state=1;
	}
	else{
		GPIO_setOutputLowOnPin(this->port,this->pin);
		this->state=0;
	}
}
void GPIO::gpio::assignPort(uint8_t port){ this->port=port; }
void GPIO::gpio::assignPin (uint16_t pin){ this->pin=pin;   }
void GPIO::gpio::operator!(void)	{
	GPIO_toggleOutputOnPin(this->port,this->pin);
	this->state=!this->state;
}
void GPIO::gpio::enableInterrupt()	{ GPIO_enableInterrupt(this->port,this->pin);}
void GPIO::gpio::setAsInputPinWithPullUpResistor()	{ GPIO_setAsInputPinWithPullUpResistor(this->port,this->pin);}
void GPIO::gpio::setAsInputPinWithPullDownResistor()	{ GPIO_setAsInputPinWithPullDownResistor(this->port,this->pin);}
void GPIO::gpio::toggleOutputOnPin()	{
	GPIO_toggleOutputOnPin(this->port,this->pin);
	this->state=!this->state;
}
void GPIO::gpio::setAsPeripheralModuleFunctionInputPin()	{ GPIO_setAsPeripheralModuleFunctionInputPin(this->port,this->pin);}
void GPIO::gpio::setAsPeripheralModuleFunctionOutputPin()	{ GPIO_setAsPeripheralModuleFunctionOutputPin(this->port,this->pin);}
void GPIO::gpio::setAsInputPin()	{
	GPIO_setAsInputPin(this->port,this->pin);
	this->state=this->getInputPinValue();
}
void GPIO::gpio::setAsOutputPin()	{ GPIO_setAsOutputPin(this->port,this->pin);}
uint8_t GPIO::gpio::getInputPinValue()	{ return GPIO_getInputPinValue(this->port,this->pin);}
void GPIO::gpio::disableInterrupt()	{ GPIO_disableInterrupt(this->port,this->pin);}
uint16_t GPIO::gpio::getInterruptStatus()	{ return GPIO_getInterruptStatus(this->port,this->pin);}
void GPIO::gpio::clearInterrupt()	{ GPIO_clearInterrupt(this->port,this->pin);}
void GPIO::gpio::setDriveStrength(uint8_t strength)	{ GPIO_setDriveStrength(this->port,this->pin,strength);}
void GPIO::gpio::selectInterruptEdge(uint8_t edge)	{ GPIO_selectInterruptEdge(this->port,this->pin,edge);}

