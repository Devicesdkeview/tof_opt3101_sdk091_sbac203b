/*
 * portAssign.hpp
 *
 *  Created on: Nov 10, 2017
 *	  Author: a0875461
 */

#ifndef PORTASSIGN_HPP_
#define PORTASSIGN_HPP_

//#include <device.h>

extern "C"
{
	#include "MSP430/driverlib/MSP430F5xx_6xx/driverlib.h"
}


#include <stdint.h>


namespace GPIO {
	class gpio {
		private:
			uint16_t pin;
			uint8_t port;
		public:
			uint8_t state;
			void operator=(uint8_t);
			void operator!(void);
			void assignPort(uint8_t);
			void assignPin(uint16_t);
			void enableInterrupt();
			void setAsInputPinWithPullUpResistor();
			void setAsInputPinWithPullDownResistor();
			void toggleOutputOnPin();
			void setAsPeripheralModuleFunctionInputPin();
			void setAsPeripheralModuleFunctionOutputPin();
			void setAsInputPin();
			void setAsOutputPin();
			uint8_t getInputPinValue();
			void disableInterrupt();
			uint16_t getInterruptStatus();
			void clearInterrupt();
			void setDriveStrength(uint8_t);
			void selectInterruptEdge(uint8_t);

	};
}


#endif /* PORTASSIGN_HPP_ */
