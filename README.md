This is the code for the STM32 (F4) part of the HIL project in conjunction with the RPi. 
The objective is for the STM32 to be able to act as a generic HIL board to be able to simulate peripherals on the boards of our University's solar car.
This includes protocol drivers, peripheral logic, and DACs to simulate analog signals.
The most recent update is that a lot of the firmware infrastructure has been developed (ie. UART, SPI, and I2C protocol drivers, UART comms, DAC driver, and some peripheral mocking), but there is still peripheral mocking and integration testing work that needs to be done.
The work is still in progress, so there should be more to come!
