<p align = "center">
<img src = "Design/Logo/logo_outline_black.png" width = "70%" title = "Logo">
</p>

> **Arduino-powered device** for _near-field_ **remote control of multiple power outlets**. 
> 
> The device can be programmed and scheduled with timers thanks to its internal clock. 
> 
> It can be **easily configured using its Android app** counterpart, which is designed for devices operating with Android provided of a _bluetooth transmitter_.
> 
> The app also supports **voice commands** with a very simple syntax, which makes it easy to use.

# CENTRALINO
_Your world in your hand._
<p align = "right">
Last modified: 19th June 2017
</p>

## Hi, I'm Filippo 👋
This is a very old project of mine, it was born in January 2017 and concluded in June the same year. 
This was my first project in the field of electronics and programming.
I was 17 years old and I guess you can tell I was a bit naive, but I was very passionate about it and I still am.

This project has many flaws, but it was a great learning experience, I'm quite fond of it, so I decided to share it here as something to remember. 

Something that will always suggest how ...
<p align = "right">
<b>...every long journey begins with a first step.</b>
</p>

------------------------------------------------------
##### Small note on language 🇮🇹 🇬🇧:
The project was born in Italian, so unfortunately many of the comments in the code as well as documentation and the report are in Italian.
I apologize for this, but I hope that the code is still understandable and that the documentation is still useful (maybe with the help of a translator).
However, I decided to have at least the README in English, so that the core of the project as well as the repository structure is understandable to everyone.

### Project reference sector.
Novel Technologies, Internet of Things (IoT), Home Automation.

### Idea and objective:

The project was born with the purpose of making residential and working complex more connected to the people who inhabit it. The project aims to enhance humans environmental control. 
CENTRALINO is designed to control electrical devices such as household appliances, electric, air conditioners, heating systems, and similar.
This centralization of control can, in some cases, change a person's experience with the surrounding world. The CENTRALIzation of automation is sometimes not just a convenience but a necessity, i.e. in case of subjects with disabilities. In such cases, "smart homes" are a topic that companies are vigorously addressing to offer increasing automation and integration between systems and services. 
Home automation involves a complex mix of various technologies and requires strong interdisciplinary collaboration.

Therefore, the project aims to:

 - Enhance security of electrical devices populated environments.
 - Reduce operating costs.
 - Convert old environments and old systems into more dynamic ones.
 - Simplify the design, installation, maintenance, and use of technology.
 - As a whole: improve the quality of life.

### Description of the project:

The project is named "CENTRALINO" (Italian for "switchboard"), the name reflects its function of both **centralizing** and **managing** control, much like in telecommunications. 
It is a device that allows remote control of multiple power outlets with the ability to be programmed and scheduled at specific intervals using an internal clock. The device is easily configured with mobile devices such as phones, tablets, or computers. The latter only needs to support applications designed for Android operating systems and have a Bluetooth transmitter.

### Functions

Currently, there are three main functions, but the most important aspect is that there is a foundation that anyone can use to develop their own custom functions. 

1. **Instant On/Off** - Instantaneous switching on and off of the selected device (which means indirect control on its power outlet). 

2. **On/Off with alarm** - Similar to the previous function, but with the possibility of specifying a time at which the device will be turned on or off.

    To do so the device uses the RTC (Real-Time Clock) to compare CENTRALINO's time with the user-set "alarm" time.

3. **On/Off with a timer** - Similar to the previous function, but with the possibility of specifying a duration after which the device will be turned off.

#### How is the CENTRALINO device set to the current time? 
It receives the timer duration in minutes from the Android app counterpart and sets the RTC accordingly.

### Tools used (Software).

 -  Fritzing: is a free software for electronic design, focused on the transition from simple prototypes to the printed circuit board to be sent to production. Useful for designing the prototype of the circuit even before it is built.
 - Arduino IDE: is the integrated development environment (Integrated Development Environment) of Arduino, it is a multiplatform application in Java used to compile the code with which the microcontroller that manages the sensors and other components is programmed.
 - Python interpreter: It is a high-level, object-oriented, suitable programming language, among other uses, for developing distributed applications, scripting, numerical computation and system testing. Useful for writing and running programs for Windows, Android and a selected distribution of Linux.
 - Android AppInventor: It is a web application that allows you to create applications for Android operating systems using a graphical interface. Useful for creating the application that will be used to control the device. 

### Tools used (Hardware):

 - Welder.
 - PonD.
 - Cellulose adhesive tape.

### Components used (Hardware):

     • Jumpers for solderless male-male connections.
     • Bread Board for experimental prototypes of solderless circuits.
     • Infrared emitting LEDs.
     • Infrared receiver.
     • Buttons/Buttons.
     • Bluetooth transceiver module – module for Bluetooth transmission and reception.
     • Micro SD Mini Slot – Module for connection with a micro SD card for data storage.
     • Assortment of resistors from 1 to 10 M Ohm (Ω).
     • RTC (Real Time Clock) Real Time Clock – module with battery.
     • Micro ATmegax32u4 powered by 5V (microcontroller).

### Cost of components:

Prices are taken from the following sites:
     - AliExpress: is a branch of the "Alibaba Group" company that unites Chinese companies and offers a retail service to an international market, mainly targeting European buyers. It is the supplier of our components.

     • Jumpers = 120 pieces for €2.39.
     • Bread Board = 2 pieces for €0.74.
     • Infrared LEDs = 20 pieces for €1.25.
     • IR receiver = 10 pieces for €0.73.
     • Buttons/Buttons = 100 pieces for €1.44.
     • RTC (Real Time Clock) = 1 piece for €1.20.
     • Assortment of resistors = 300 pieces for €1.62.
     • Bluetooth = 2 pieces for €2.73 each.
     • Micro SD Mini slot = 2 pieces for €0.47 each.
     • Micro ATmegax32u4 = 3 pieces for €4.59 each.

TOTAL = 

    2.39 * 1 + 0.74 * 2 + 1.25 * 1 + 0.73 * 1 + 1.44 * 1 + 1.20 * 1 + 1.62 * 1 + 2.73 * 2 + 0.47 * 2 + 4.59 * 3 
= €30.92

------------------------------------------------------

### Known issues:

Concerning the Instant On/Off function:
For greater safety, future security measures should be implemented to prevent continuous switching on and off of the same outlet to avoid damaging the connected devices and the microcontroller itself.

Concerning voice commands:
The voice commands syntax is very simple, but it is also very limited. It is not possible to deviate even just a little without incurring in unrecognized commands. This is due to the total absence of natural language processing, which in 2017 I dint know how to implement.

Concerning InfraRed communication:
The code structure of the device is able to eventually support infrared communication, but it is not implemented yet. However the physical circuitry is designed to support it.

### Main issues:
As we still have to delve into the project, the problems are still being studied, however some appear obvious:
     • Studying computer languages in an indigenous way, time represents the biggest obstacle for this problem, everything can be learned if you have enough time to try and try again what you are creating. There are 3 (approximately) languages to learn. Java, Python and C (despite its affinities with C++ learned at school, writing with C involves some differences).
     • The search for specific and as approximate documentation as possible. This research concerns everything we have to study on our own (practically everything, from the PRACTICAL side), in fact these documents are less easy to find than one might think. It may seem trivial but when you find yourself having to connect all the sensors and the different components it is more than a good idea to have done in-depth research regarding the current voltages of each one, the types of connections, the types of communication protocols used and all the small details relating to each of them. Same thing goes for all software used (as far as knowing the details is concerned).
     • The BIGGEST problem is undoubtedly the one linked to funds. In fact, the components we are going to buy are rather "convenient", for two reasons:
         1. Because it is a prototype.
         2. (Most relevant reason) Because we don't have the funds to pay for more accurate and better made components. The ones we are buying are clones. Their creation is possible thanks to the fact that this market sector is almost strictly open source and therefore allows each manufacturer to produce their own components even if they are of poor quality. The "better" components would cost much more than we can afford. (For example, the same microcontroller we are buying at €4.59 each "officially" costs €20 and is certainly of better quality, however it is not a choice that we can consider for our funds).
     • Convince the class council to accept this project.

Date
Castellani Filippo
01/20/2017

### Project report

It is possible to find the project report [here](/Project_Report/Relazione%20progetto%20CENTRALINO1862017.pdf)
