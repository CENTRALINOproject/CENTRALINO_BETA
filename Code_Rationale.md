# Arduino and Android code rationale
-----------------------------------------------------------

## Rationale behind the Arduino code structure

Referring to the latest version of the code, available [here](/Design/Software/CLIENTino_versions/CLIENTinoPRESENTATION1_1/CLIENTinoPRESENTATION1_1.ino).

### Brief overview of the code structure:
The code utilizes two data structures named `function` and `relay`. 

The `function` structure is responsible for containing the information received through Bluetooth packets, while the `relay` structure is responsible for storing information related to the physical device's outlets. 

Each `relay` structure will have its own:
 - activation and deactivation times, 
 - a timer,
 - a numerical description to indicate on which physical relay to issue a command, especially the pin address so that the microcontroller knows where to send the activation/deactivation signal. 

#### How is the information received from the Bluetooth packets stored?

An additional layer on top of the Bluetooth communication system was created to make the system more flexible. Bluetooth covers all seven levels of the ISO/OSI, but with an additional layer, it is possible to managae different power outlets an the same CENTRALINO (making this comunication mean flexible to our purspose).

#### Bluetooth Packet Structure:

##### Initiator and terminator:
Each Bluetooth packet consists of 16 bytes and has a packet initiator "[" (ASCII: 91) and a terminator "]" (ASCII: 93). 
Without these, it would be impossible to determine when a packet begins or ends, making byte stream handling much more manageable. 

##### Content and divisions:
Inside the packet, there are additional divisions indicated by the symbol "," (ASCII: 44). It helps determine the beginning and end of each packet sector, providing greater packet integrity (in the case of erroneous transmissions, if there are no ",", the packet will not be considered valid. For a better understanding, refer to the "void bluetooth_Parser()" function). 

**Packet final structure**

[ Activity (2 digits) , Extra_value (4 digits) , Extra_value2 (6 digits) ]

 - `Activity` varies based on Wake-up/Timer and On/Off. 
 - `Extra_value` contains the pin number to which the command should be directed. 
 - `Extra_value2` contains, in the case of "Wake-up," the time in the hh:mm:ss format, and in the case of "Timer," the time in milliseconds.

##### Activity handling:
The system also has an "activity handler"; it serves to manage packets once they have been "routed" and understand the actions required. 

The variable `activity` mentioned in the previous point stores the code corresponding to the action the microcontroller must perform (e.g., 01 and 02 are the `activity` corresponding to instantaneous power On and Off). 

In `Extra_value`, is stored the device number, the packet refers to, so the value found in `rel[x].socket` is, in fact, the pin to which the relay is connected and to which `Extra_value` refers (this mechanism makes it possible to address packets to individual devices, similarly to a "MAC address"). 

In `Extra_value2`, you can find the supplementary value that supports the "activity." For example, the times for "alarms" expressed as "001650" (for integrity reasons, they are always six digits). The one just mentioned is an alarm for 16:50.
> Example packet: "[03,0006,001650]". It sets a power-on alarm for 16:50 on pin 6.

### Main Challenges

#### Limitations of the microcontroller:
The microcontroller lacks an internal clock, making it impossible for it to determine the time during activities. This required the use of an external component, a Real-Time Clock module, to manage the time. 

However, this component does not have alarm or timer functions, so the microcontroller had to handle time and activity deadlines on its own. 

Additionally, there was the issue that if two `relay` structures had the same deactivation time and the time for acquiring the time was too slow, the system might be too slow to manage the alarms. This was resolved with the "void turn_by_match()" function, which checks each individual `relay` structure in times well below a second and ensures that multiple `relays` can be turned on/off simultaneously, even when the times coincide down to the second.

#### Automatic retrieval of the number of devices connected to CENTRALINO by the app:
To inform the application about the devices connected to the device, and for this purpose, a superficial description of the power outlets was required. Thus, the `description` variable with a legend (referred to in the code as MEANINGS OF DESCRIPTION) was introduced. The mechanism through which the application learns about the various `descriptions` of the `relay` structures is as follows:

> - The software application sends a packet with activity = 50, i.e., a Discovery (requesting information to be sent).
> - The device sends as many packets as there are "relay" structures with activity = 51 and the respective rel[].description (the description of each structure)
> - Finally sends a packet with activity = 99, which means that the relays have been completed, and the application can stop waiting for more information.

----------------------------------------------------------- 

Referring to the latest version of the code, app .apk available [here](/Design/Android_Centralino/App_builds/STABLE_CENTRALINO1_3.apk)

## Rationale behind the Android app code structure

### Brief explanation
The application mainly uses the use of global variables that are continuously used in block to send packets with the `activity`. These three variables take their name from the physical device system CENTRALINO, therefore they are also called `activity`, `extra_value` and `extra_value2`.

#### Animations
The animations are minimal and take place thanks to the "expansion" of self-moving areas that move the contents of the page to be displayed by the user. When a button is pressed, the cycle starts that "expands" the "push_container" (both "right" and "left") with variables that increase the area covered on the screen. Once "Left_container" and/or "Right_container" have moved, they remain in the position they are in until the next button press.

#### Bluetooth picker
The bluetooth_picker allows you to choose between devices associated with the phone quickly and intuitively.

#### Voice command recognition
Voice command recognition takes place by identifying specific words within a sentence. If the words "turn on" or "turn off" are present in the spoken sentence, the algorithm searches the rest of the sentence for the name of a device that it knows to be connected to the device. If the device is found, the application sends the appropriate signal, otherwise it signals it with a sound notification.

#### On the infrastructure of the app
The App Inventor development platform is based on the use of events. Android events act as a system kernel. They allow you to always know when a certain action has occurred and therefore allow you to call specific functions when those "events" occur. For example, when a button is pressed, it will raise the button.onclick() event and it will be possible to call your own "procedure" (function) whenever the event is raised. Events are many and very varied. The events related to the screen, i.e., "screen.BackPressed()" and "screen.Initialize()", the events related to the buttons of various types ("timePicker" and similar) have been mainly used, and as can be seen from the operating code, the tinyDB object/component with its various methods and functions has been widely used.

### Main Challenges

#### Handling events 
Personally, the transition from a traditional programming system to a more articulated one can be hard. Knowing that the code does not always do the same operations in sequence but behaves differently based on the events that arise is very different from what I was used to.

#### Absence of documentation
Not being App Inventor a real programming language, it is very rare to find reliable documentation on the syntax of the commands, fortunately, their operation is very intuitive, but in cases where this intuitiveness has failed, there was a need to spend a lot of time in research and understanding of commands suitable for the pursuit of objectives.

#### App Inventor limitations
A big problem was found in the use of App Inventor itself precisely because it is a platform under development and is still in the BETA phase, it is often subject to crashes, bugs of various kinds, and frequent interruptions of partial operation.
