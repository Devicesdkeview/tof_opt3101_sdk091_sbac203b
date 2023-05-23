/*
 * MSPConnections.hpp
 *
 *  Created on: Dec 1, 2017
 *      Author: a0875461
 */

#ifndef MSPCONNECTIONS_HPP_
#define MSPCONNECTIONS_HPP_

#include "MSP430/gpio.h"
#include "../definitions.h"

extern "C"
{
	#include "MSP430/driverlib/MSP430F5xx_6xx/driverlib.h"
}


//#include "colorLED.hpp"

namespace LAUNCHPAD {
	class MSPConnections {
		public:
			GPIO::gpio rstz;
			GPIO::gpio gp1;
			GPIO::gpio gp2;
			GPIO::gpio gp3;
			GPIO::gpio gp4;
			GPIO::gpio scl_s;
			GPIO::gpio sda_s;
			//LED::multiColorLED *ledIndicator;
			void init(void);
	};
}


#endif /* MSPCONNECTIONS_HPP_ */
