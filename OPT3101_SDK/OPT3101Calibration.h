/*!
* \file OPT3101Calibration.h
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
* This file contains the OPT3101::calibrationC class declaration
*/

#ifndef OPT3101CALIBRATION_H_
#define OPT3101CALIBRATION_H_

#include <cmath>
#include "OPT3101DesignCoefficients.h"
#include "OPT3101frameData.h"
#include "OPT3101PhaseOffset.h"
#include "environmentControl.h"

#ifdef OPT3101_USE_STREAMLIB
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#endif

/** \brief environmentalController class instance declaration
This global variable declaration to be available across files which controls the environmental parameters. The instance is of class environmentalController
*/
extern environmentalController envController;

namespace OPT3101 {
	/**
	OPT3101 systems require various calibrations for accurate measurement. During the calibration process there are several coefficients which needs to be measured and analyzed. 
	Although the calibration settings can be stored as register settings, they would not be very meaning full to understand and analyze. 
	This class acts as an intermediate translator to measure, store and calibration values. The class also invokes methods to convert the calibration coefficients to register settings to load to the device. 
	There are several members of this class where more than 1 instances of those members are required. The class only contain pointers for these coefficient classes. 
	The constructor definition of this class is generated by OPT3101 configurator tool. The file generated by the tool can be directly imported to this project for a complete operation SDK. 
	*/
	class calibrationC {
		public:
			crosstalkC internalCrosstalk[1]; ///< Pointer to analyze and store internal crosstalk class OPT3101::crosstalkC
			crosstalkC illumCrosstalk[3][2]; ///< Pointer to analyze and store illumination crosstalk class OPT3101::crosstalkC
			phaseOffsetC phaseOffset[3][2]; ///< Pointer to analyze and store phase offset class OPT3101::phaseOffsetC
			crosstalkTempCoffC illumCrosstalkTempCoff[3][2]; ///< Pointer to analyze and store crosstalk temperature coefficients OPT3101::crosstalkTempCoffC
			phaseTempCoffC phaseTempCoff[3][2]; ///< Pointer to analyze and store phase temperature coefficients OPT3101::phaseTempCoffC
			phaseAmbientCoffC phaseAmbientCoff[1]; ///< Pointer to analyze and store phase ambient coefficients OPT3101::phaseAmbientCoffC
			uint8_t registerAddressList[64]; ///< List of OPT3101::registers address which needs to be stored as calibration for the system.
			uint8_t registerAddressListSize; ///< Number of OPT3101::registers address that need to be stores as calibration for the system 
			bool EEPROM_connected; ///< Flag to specify if EEPROM is connected to the OPT3101 device 
			bool extTempSensor_connected; ///< Flag to specify if external temperature sensor is connected to the OPT3101 device
			uint8_t recordLength; ///< Specifies the length of records to be stored for calibration configurations. This is set be OPT3101 configurator tool. 
			/*!
			* \brief Dummy function for documentation
			* This function is to just document the functionality of the constructor
			* \returns Nothing;
			*/
			calibrationC(bool dummyFlag);
			/*!
			* \brief Constructor for class OPT3101::calibrationC
			*  Constructor definition for which comes from the OPT3101 configurator tool. Allocates memory for all the calibration coefficient classes. 
			*  Since the actual allocation depends on the configuration of the system, this is generated by the configurator tool.
			*/
			calibrationC();
			/*!
			* \brief Finds common crosstalk scale coff to be applied 
			* OPT3101 system could consist of multiple TX configuration operating together, switching between each other configurations. In such cases more than 1 illum crosstalk compensation registers needs to be applied however OPT3101 has only one common scale which this method computes
			* \param[in,out] illumXtalk; illumXtalk is pointer to OPT3101::crosstalkC class which contains the list of crosstalk instances for which the common coefficient needs to be calculated. 
			* \param[in] txActiveList;
            * \param[in] registerSetActiveList;
			* \returns Nothing;
			*/
			void findCommonCrosstalkScale(crosstalkC *illumXtalk, bool *txActiveList,bool *registerSetActiveList);
			/*!
			* \brief Calculates crosstalk temp coefficient registers from floating point precision coefficients
			* OPT3101 system could consist of multiple TX configuration operating together, switching between each other configurations. In such cases more than 1 illum crosstalk temperature compensation registers needs to be applied.
			* OPT3101 has only one common scale which this method computes along with the registers that need to be written to compensate these effects. 
			* \param[in,out] illumXtalkCoff; illumXtalkCoff is pointer to OPT3101::crosstalkTempCoffC class which contains the list of crosstalk temp coefficients for which the register values needs to be calculated.
			* \param[in] txActiveList;
            * \param[in] registerSetActiveList;
			* \param[in] illumXtalk; illumXtalk is pointer to OPT3101::crosstalkTempCoffC class which contains the list of crosstalk instances for which the common coefficient needs to be calculated. This is mainly required to scale the crosstalk values with magnitude
			* \returns Nothing;
			*/
			void findCrosstalkTempRegisterValues(crosstalkTempCoffC *illumXtalkCoff, bool *txActiveList,bool *registerSetActiveList, crosstalkC *illumXtalk);
			/*!
			* \brief calculates the phase temp coff register values from the floating point coff 
			* OPT3101 system could consist of multiple TX configuration operating together, switching between each other configurations. In such cases more than 1 phase temperature compensation registers needs to be applied.
			* OPT3101 has only one common scale which this method computes along with the registers that need to be written to compensate these effects.
			* \param[in,out] phaseTempCoff; phaseTempCoff is pointer to OPT3101::phaseTempCoffC class which contains the list of phase temp coefficients for which the register values needs to be calculated.
			* \param[in] txActiveList;
            * \param[in] registerSetActiveList;
			* \param[in] freqCount; freqCount is frequency count register read from OPT3101::registers::freq_count_read_reg. This is used to scale the coefficients accordingly
			* \returns Nothing;
			*/
			void findPhaseTempRegisterValues(phaseTempCoffC* phaseTempCoff, bool *txActiveList,bool *registerSetActiveList, uint16_t freqCount);
			/*!
			* \brief reports members of the instance
			*  Print the members of the class instance on screen
			* \returns Nothing;
			*/
			void report();
	};
}

#endif /* OPT3101CALIBRATION_H_ */
