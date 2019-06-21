# Arduino_ATX_OSSCAL-Calibration


This repo contains arduino code for the two programs used to calibrate the OSSCAL internal RC calibration variable.


It functions between the arduino and an arduino compatible chip that is functioning without an external clock. The internal clock of an uncalibrated chip is within 10% of the advertised clock speed. By modifying the OSSCAL, that variance can drop to below 1%, allowing for serial communications to occur.


To utilise the software, upload the AtTiny program to the chip, and the AutoCalibrate program to the arduino. (Further instructions are within the files themselves.)


From there, connect the two devices together and apply power. The arduino will continually poll the output of the target chip and will compare with its own generated output. It will then modify the target chip's OSSCAL value to guide the outputs closer and closer together.


Eventually the outputs will match, or osscillate between two OSSCAL values, at which point the OSSCAL value can be saved and written into future software for the target chip, automatically calibrating it on boot.