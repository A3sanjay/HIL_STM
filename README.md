This is the code for the STM32 (F4) part of the HIL project in conjunction with the RPi.
The objective is for the STM32 to be able to act as a generic HIL board to be able to simulate peripherals on the PCBs of our University's solar car.
This includes protocol drivers, peripheral logic, and DACs to simulate analog signals.
The most recent update is most of the core firmware infrastructure has been developed (ie. UART, SPI, and I2C protocol drivers, UART comms with RPi, ProtoBuf integration and encoding/decoding, DAC driver, and most of the peripheral mocking), but there is still some integration testing that needs to be done.
This is intended to be a longer-term project, so the next steps would be looking into developing more advanced features and improving upon existing features/implementations (eg. switching to G/H series STM32 MCU)!
