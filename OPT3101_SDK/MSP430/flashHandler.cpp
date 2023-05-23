/*
 * flashHandler.cpp
 *
 *  Created on: Nov 21, 2017
 *	  Author: a0227156
 */

#include "flashHandler.h"
#include "../hostController.h"

STORAGE::flashHandler::flashHandler(void) {

	// pointers to first byte of banks B,C,D
	this->baseLocationPtr = (uint8_t*) 0x1800;
	//this->memorySize =0x180;
}

//bool STORAGE::flashHandler::read() {
	//return this->read(this->readPtr);
//}

void STORAGE::flashHandler::read(void) {
	this->read(0,this->data,this->memorySize);
}
void STORAGE::flashHandler::write(void) {
	FlashCtl_write8(this->data,this->baseLocationPtr,this->memorySize);
}

void STORAGE::flashHandler::erase(void) {
	uint16_t c;
	uint8_t status;
	for(c=0;c<0x180;c+=0x80){
		do{
			FlashCtl_eraseSegment(this->baseLocationPtr+c);
			status=FlashCtl_performEraseCheck(this->baseLocationPtr+c,0x80);
		}while(status==0x00);
	}
}


bool STORAGE::flashHandler::read(uint16_t location,uint8_t *data,uint16_t length) {
	uint16_t c;
	if((location+length)>this->memorySize)
		return false;
	for(c=0;c<length;c++){
		*(data+c)=*(this->baseLocationPtr+location+c);
	}
	return true;
}

bool STORAGE::flashHandler::write(uint16_t location,uint8_t *data,uint16_t length) {
	uint16_t c;
	if((location+length)>this->memorySize)
		return false;

	this->read();
	for(c=0;c<length;c++)
		this->data[location+c]=data[c];
	this->erase();
	this->write();
	return true;
}
