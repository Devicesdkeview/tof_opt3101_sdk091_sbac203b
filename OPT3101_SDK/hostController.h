/*! 
* \file hostController.h
* \author  Karthik Rajagopal <krthik@ti.com>
* \version 0.9.1
*
* \section COPYRIGHT
* TEXAS INSTRUMENTS TEXT FILE LICENSE
* Copyright (c) 2018 Texas Instruments Incorporated
* All rights reserved not granted herein.
* Limited License.
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive license under copyrights and patents it now or hereafter owns or controls to make, have made, use, import, offer to sell and sell ("Utilize") this software subject to the terms herein.  With respect to the foregoing patent license, such license is granted  solely to the extent that any such patent is necessary to Utilize the software alone.  The patent license shall not apply to any combinations which include this software, other than combinations with devices manufactured by or for TI ("TI Devices").  No hardware patent is licensed hereunder.
* Redistributions must preserve existing copyright notices and reproduce this license (including the above copyright notice and the disclaimer and (if applicable) source code license limitations below) in the documentation and/or other materials provided with the distribution
* Redistribution and use in binary form, without modification, are permitted provided that the following conditions are met:
* * No reverse engineering, decompilation, or disassembly of this software is permitted with respect to any software provided in binary form.
* * any redistribution and use are licensed by TI for use only with TI Devices.
* * Nothing shall obligate TI to provide you with source code for the software licensed and provided to you in object code.
* If software source code is provided to you, modification and redistribution of the source code are permitted provided that the following conditions are met:
* * any redistribution and use of the source code, including any resulting derivative works, are licensed by TI for use only with TI Devices.
* * any redistribution and use of any object code compiled from the source code and any resulting derivative works, are licensed by TI for use only with TI Devices.
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers may be used to endorse or promote products derived from this software without specific prior written permission.
* DISCLAIMER.
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* \section DESCRIPTION
* This file contains the hostController class. This file contains a general template for a host controller
*/
#ifndef HOSTCONTROLLER_H_
#define HOSTCONTROLLER_H_

#include "definitions.h"

#ifdef TIMSP430F5529_LAUNCHPAD_CALIBRATION_TOOL
#include "MSP430/i2cHandler.h"
#include "MSP430/flashHandler.h"
#include "MSP430/MSPConnections.h"
extern "C"
{
#include "MSP430/hal.h"
#include "MSP430/USB_config/descriptors.h"
#include "MSP430/USB_API/USB_Common/device.h"
#include "MSP430/USB_API/USB_Common/usb.h"                 // USB-specific functions
#include "MSP430/USB_API/USB_CDC_API/UsbCdc.h"
#include "MSP430/USB_app/usbConstructs.h"
}
#include <stdlib.h> //Added to support abs function
#endif

#include <stdint.h>

#ifdef OPT3101_USE_SERIALLIB 
#include "serialLib/serial.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif /*_WIN32 */
#endif /* for OPT3101_USE_SERIALLIB */

#ifdef OPT3101_USE_STDIOLIB 
#include <stdio.h>
/*! \def filename length
This sets memory allocation length for file naming strings
*/
#define FILENAME_LENGTH 50
const char filePath[] = { "C:/temp/" };
#endif

#ifdef OPT3101_USE_SERIALLIB
/** \brief Serial Command Port  declaration
This global variable declaration with name OPT3101commandPort of class serial::Serial is used by class like OPT3101::deviceRegister for I2C read and writes.
*/
//serial::Serial OPT3101commandPort("COM4", 9600, serial::Timeout::simpleTimeout(1000));
#if defined(linux) || defined(_WIN32)
extern serial::Serial OPT3101I2CCommandPort;
#endif

#endif // SERIAL LIB

class hostController;


#ifdef OPT3101_USE_STDIOLIB 
/** \brief filePath
This global variable to declare a path to all calibration files storage 
*/
extern const char filePath[];
#endif

/** \brief hostController declaration
This global variable declaration with name host of class hostController is used by various different classes like OPT3101::deviceRegister , OPT3101::registers and OPT3101::device to specify specific instructions to the host like wait, sleep, I2C reads and writes
*/
extern hostController host;

/*! \class hostController
\brief Generic implementation for host 

As part of OPT3101SDK there are several host specific functions that need to be performed. Examples of such functions are writing or reading from I2C ports, sending reset pulse to OPT3101 device<br>
These implementations are very specific to the host on which the SDK is ported and run. <br>
This abstract class provides a template with self explanatory method names which the users can override and implement their own functions. <br>
Example code is provided for OPT3101EVM with implementations for a windows 10 PC. 
*/
class hostController {
	public:
        /*!
        * \brief constructor mostly used to initialize the host
        *
        * Method to mostly initialize host. Especially for MSP like hosts.
        * \return Nothing
        */
        hostController(void);
		/*!
		* \brief method to read data from I2C port
		*
		* \param[in] address; address is the I2C register address 
		* \return value; value read from I2C port for the address
		*/
		uint32_t readI2C(uint8_t address);
		/*!
		* \brief method to write data from I2C port
		*
		* \param[in] address; address is the I2C register address
		* \param[in] data; data to write to I2C register 
		* \return Nothing
		*/
		void writeI2C(uint8_t address, uint32_t data);
		/*!
		* \brief send reset pulse to OPT3101 device
		* Method used to send reset pulse to OPT3101 device
		* \return Nothing
		*/
		void resetDevice();
		/*!
		* \brief sleep host 
		* Method used to sleep or make host wait for a particular amount of time specified in milliSeconds
		* \param[in] timeInMilliSeconds; Time for which the host needs to sleep specified in milliSeconds
		* \return Nothing
		*/
		void sleep(uint32_t timeInMilliSeconds);
		/*!
		* \brief sleep host
		* Method used to sleep or make host wait for a particular amount of time specified in number of data ready pulses from OPT3101
		* \param[in] dataReadyCounts; Time for which the host needs to sleep specified data ready pulses from OPT3101
		* \return Nothing
		*/
		void sleepDataReadyCounts(uint16_t dataReadyCounts);
		/*!
		* \brief pause host 
		* Method used to make host wait for user input or interrupt. Useful for debug
		* \return Nothing
		*/
		void pause();
        /*!
        * \brief initialize host
        * Method to initialize host. Especially for MSP like hosts.
        * \return Nothing
        */
        void initialize();
        /*!
        * \brief print message
        * Method to print message on host to user
        * \return Nothing
        */
        void printf(const char *fmt, ...);
        /*!
        * \brief print Sets color for terminal
        * Method sets colors for terminals
        * \return Nothing
        */
        void printfSetColor(uint8_t color=0xFF);


#ifdef TIMSP430F5529_LAUNCHPAD_CALIBRATION_TOOL
		I2C::i2cHandler i2c;
		STORAGE::flashHandler flash;
		LAUNCHPAD::MSPConnections gpio;
#endif

};


#endif /* HOSTCONTROLLER_H_ */
