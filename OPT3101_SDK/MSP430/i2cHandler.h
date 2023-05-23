/*
 * i2cHandler.hpp
 *
 *  Created on: Nov 19, 2017
 *      Author: a0875461
 */



#ifndef I2CHANDLER_HPP_
#define I2CHANDLER_HPP_
extern "C"
{
#include "hal.h"
}
#include <stdio.h>

namespace I2C {
	class i2cHandler {
		private:
			uint8_t *dataTx;
            uint8_t *dataRx;
			uint8_t address;
			bool write();
			bool read();
		public:
			USCI_B_I2C_initMasterParam i2cParam;
			uint8_t slaveAddress;
			void updateSlaveAddress();
			uint8_t slaveAddress_;
			uint8_t continousReadRegisterAddress;
			uint8_t continousReadByteCount;
			uint8_t regBankSize;
			uint32_t timeOut;
			bool write(uint8_t,uint8_t*);
			bool write(uint8_t,uint32_t);
			bool write(uint8_t*);
			uint8_t* read(uint8_t);
			bool read(uint8_t,uint8_t*);
			bool read(uint8_t,uint32_t*);
			bool read(uint8_t*);
			bool continuousRead(uint8_t*);

			void init(void);
			i2cHandler(void);
			~i2cHandler(void);
	};
}

#endif /* I2CHANDLER_HPP_ */
