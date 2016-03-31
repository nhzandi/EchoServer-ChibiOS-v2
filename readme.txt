*****************************************************************************
** ChibiOS/RT port for ARM-Cortex-M4 STM32F407.                            **
*****************************************************************************

** TARGET **

The demo runs on an STM32F4DISCOVERY board + DP83848 ETHERNET PHY. Wires
connections described in board.h file.

** The Demo **

The demo currently flashes a LED using a thread and implements UDP-TCP echo server demonstration for STM32F4x7 devices on port 8000. The board IP address is "192.168.1.10".
You should change your network IPv4 parameters as defined in lwipthread.h such :

Address: 192.168.1.20 (or any other ip that is free)
Netmask: 255.255.255.0
Gateway: 192.168.1.1

Echo server is a port of ST appnote from FreeRTOS to ChibiOS.

** Build Procedure **

The demo has been tested by using the free Codesourcery GCC-based toolchain.
Just modify the TRGT line in the makefile in order to use different GCC ports.

** Notes **

Some files used by the demo are not part of ChibiOS/RT but are copyright of
ST Microelectronics and are licensed under a different license.
Also note that not all the files present in the ST library are distributed
with ChibiOS/RT, you can find the whole library on the ST web site:

                             http://www.st.com

Demo was provided by Navid Zandi based on the lwip tcp/ip stack demonstration for stm32f4x7 microcontrollers and with help from Nomados http-server port
https://github.com/Nomados/STM32F4Discovery-ethernet-PHY-DP83848-demo-ChibiOS

This code uses a newer ChibiOS version 16.1.0 than https://github.com/nhzandi/EchoServer-ChibiOS
