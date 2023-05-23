/*
 * MSPConnections.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: a0875461
 */

#include <MSP430/MSPConnections.h>

void LAUNCHPAD::MSPConnections::init(){

#ifdef TIMSP430F5529_LAUNCHPAD_CALIBRATION_TOOL
	this->rstz.assignPin(GPIO_PIN0); // Assigning RSTZ Pin as per the EVM Schematic. Pin 18 P1.4/TA03
    this->rstz.assignPort(GPIO_PORT_P2);
    //this->rstz.setAsPeripheralModuleFunctionOutputPin(); // This is so that timer can work well

    //ONLY ONE LED
    //this->ledIndicator->r.assignPort(GPIO_PORT_P1);
    //this->ledIndicator->r.assignPin(GPIO_PIN0);

    this->gp1.assignPin(GPIO_PIN6);
    this->gp1.assignPort(GPIO_PORT_P1);
    //this->gp1.setAsInputPinWithPullDownResistor();
    this->gp1.setAsInputPin();
    this->gp1.selectInterruptEdge(GPIO_LOW_TO_HIGH_TRANSITION);
    this->gp1.disableInterrupt();


    /*GP2 and 3 Interchanged (OPT3101 GPIOs)-MC*/
    this->gp2.assignPin(GPIO_PIN7);
    this->gp2.assignPort(GPIO_PORT_P2);
    this->gp2.setAsPeripheralModuleFunctionOutputPin(); // Assigning clk output for P1.0

   //NO GP3 and 4

    //No Change in pin map for i2c
    this->scl_s.assignPort(GPIO_PORT_P4);
    this->scl_s.assignPin(GPIO_PIN2);
    this->scl_s.setAsPeripheralModuleFunctionInputPin(); // Assigning this for I2C function
    this->sda_s.assignPort(GPIO_PORT_P4);
    this->sda_s.assignPin(GPIO_PIN1);
    this->sda_s.setAsPeripheralModuleFunctionInputPin(); // Assigning this for I2C function
#endif

}

