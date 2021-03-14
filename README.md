# Makerbot 
**Note this design should not be used as refrence since it's still under active development and testing process**
Makerbot is an open-source hardware platform focus on robotics and self-driving vehicle featuring WiFI, BLE, 9 DOF IMU, CAN, RS485, upto 6 Servo and 4 DC motor drive


[![Makerbot  Images1](pics/img1.jpg)](pics/img1.jpg)
[![Makerbot  Images1](pics/img2.jpg)](pics/img2.jpg)
## `Hardware` PCB and 3D design files.
### Specs:
- ESP32-WROVER-IE(16MB)
- MPU-9250,9 DOF IMU
- SN65HVD230 CAN transceiver 
- MAX3485
- PCA9685 16 channel PWM driver
- DRV8841 H-Bridge
- DS3231MZ+ RTC
### Known issues
- WiFI signal strength issue 
- Pull up resistor on IO2 causing ESP32 cannot reset properly , Do not populate R15
- Rs485 issue
- cannot read magnetometer MPU9250
- Motorshield power issue
### Todos:
- Redesign motorshield 
- Add pins name to Silkscreen
- Fix known issues in next revision

## `software` Firmware example.
## `docs` Documents.
Website: https://makerviet.org/