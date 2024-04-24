ZEVonUDS an Implementaion of an Automotive Diagnostic Communication Stack for Raspberry Pi
===============================================

Getting Started on Raspberry Pi
-------------------------------

You will first need to have a Raspberry Pi and equip it with a PiCAN 2 add on

Follow the instructions found [here](https://raspberry-valley.azurewebsites.net/ref/Raspberry-Pi-PICAN2-Hat-User-Guide.pdf) to set up the CAN bus network on your Pi and to get started with SocketCAN.

Clone the repository and compile the needed files using gcc

`gcc main.c app.c dcm.c dem.c lib.c -o my_applicaiton`

You can now run the application 

Getting Started on CANoe
-------------------------------
You must first have access to the Vector tools CANoe and CANdelaStudio

Download the Vector tools files and open the CANoe files in CANoe, you may need to add the ecu1 file seperatly if it is not done automatically.

If you have acess to CANdelaStudio you can open the .cdd file here and alter it to your will. If you are satisfied this will need to be imported into CANoe through the Diagnostics menu in CANoe


Resources Used During Development 
-------------------------------
PiCAN 2 User Guide: https://raspberry-valley.azurewebsites.net/ref/Raspberry-Pi-PICAN2-Hat-User-Guide.pdf
SocketCAN - Controller Area Network, The Linux Kernal: https://docs.kernel.org/networking/can.html
CANdela Studio - Introduction + CDD file creation: https://www.youtube.com/watch?v=ldnZV5VF1BI
ZEVonUDS - SAE J1979
Various Vector Tool documentation 
ISO 156765 - CAN Transport Layer Specifictaion
