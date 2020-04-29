## Power Supply Widget

#### This is a Qt Widget for viewing and controlling the Rhode&Schwarz HMP4040 power supply using its ethernet interface.

Requirements:
- c++14
- Qt5
- CMake

How to use:
- Setup the power supply to meet your network requirements using its button panel settings
- Make sure you can reach the power supply from the client computer by sending a ping
- Include this code into your project
- Create the objects like shown in this main.cpp file
- Call the 'HMP4040Driver' class member function 'open( address, port )' using the address and port that you specified while setting up the power supply
