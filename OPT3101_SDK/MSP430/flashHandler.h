/*
 * flashHandler.h
 *
 *  Created on: Nov 21, 2017
 *	  Author: a0227156
 */

#ifndef FLASHHANDLER_H_
#define FLASHHANDLER_H_


extern "C"
{
	#include "MSP430/driverlib/MSP430F5xx_6xx/driverlib.h" //just need this for flashctl.h
}

namespace STORAGE {

	class flashHandler {
		/*
		 * Allows access to MSP430F5502 flash storage.
		 */
		private:
			static const uint16_t memorySize=0x180;
			uint8_t *baseLocationPtr;
			uint8_t data[memorySize];
			void read(void);
			void write(void);
			void erase(void);
			//bool erase(uint8_t *flashPtr, uint8_t len);
		public:
			flashHandler(void);
			bool read (uint16_t location,uint8_t *data,uint16_t len);
			bool write(uint16_t location,uint8_t *data,uint16_t len);
	};
}

#endif /* FLASHHANDLER_H_ */
