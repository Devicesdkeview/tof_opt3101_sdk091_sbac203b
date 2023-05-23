-----------------------------------
Release notes for OPT3101SDK v0.9.1
-----------------------------------

Please note this is a pre-release note with limitation. A full version v1.0.0 will be released to the ti.com website with minor enhancements. For instructions on using this SDK please refer to the "OPT3101 SDK Users Guide.pdf" file included in the SDK root directory.

Summary of Changes:
-------------------

o OPT3101SDK has been improved to make this a full functional calibration tool directly compatible with MSP430F5529 Launchpad. 
o Several bug fixes have been incorporated based on testing on different scenarios. 
o The architecture of the perDesignCalibration routines have changed. 
o Log messaging have been added to the MSP platform as well which output color information through the COM port when viewed though a terminal emulator on PC. 
o Visual studio project files and the Code composer studio files have been included in the zip file to make it easier for user to import the project. 
o Limitation: The OPT3101-configurator tool needs to be updated to match with some changes done to SDK. Users have to perform a manual step after OPT3101_Configuration.cpp generaation to make it compatible with the SDK. 

Detailed Changes:
----------------
o New file added : definitions.h 




