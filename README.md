# Stewart-Platform-PID-Controller

| :exclamation: Please be aware that the code in this repository is not the latest version. :exclamation:<br> I have not pushed the recent updates from my local repository and my laptop which contains the updated code, is currently inoperable. |
|--------------------------------------------------------------------------------------------------------------------------------------|

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)\
\
An Arduino controlled Stewart Platform with a PID Controller.

## Description

This project uses a Stewart Platform with a Touchscreen and PID controller to balance a ball.

## Installation

```
git clone https://github.com/trevortomlin/Stewart-Platform-PID-Controller.git

Copy libraries to Arduino Library Folder
cp -r Stewart-Platform-PID-Controller/arduino/PIDController Stewart-Platform-PID-Controller/arduino/StewartPlatform Stewart-Platform-PID-Controller/arduino/Vector3 ~Arduino/libraries/

If you are using the Arduino IDE:
Upload StewartPlatform.ino to your board.

If you are using the Arduino-CLI:
```

## Parts Needed
* 6x MG996r servos
* 3D Printer
* Various M3 Screws
* 12x M3 Turnbuckles
* 6 M3 x 150mm rods
* 6 Servo Horns
* PCA9685 Servo Driver

## Technologies Used
* C++
* Fusion360

## Improvements
Servos and/or code is not accurate enough and needs to be fixed.

## License
This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.
