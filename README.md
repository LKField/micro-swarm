# Micro Swarm 

##  Purpose

Micro Swarm is a project for the Micro Challenge Course in the Master in Design for Emergent Futures Year 1 for 2024-2025 to test 'swarm intelligence' using a series of [Barduino (ESP32)](https://fablabbcn-projects.gitlab.io/electronics/barduino-docs/) devices. With an input from a human user (vibration sensor), a note will be played on a single 'Reference' device. Using OpenAI, a harmonizing note will be determined and relayed to the 'Cell' devices via MQTT. The 'Cell' devices will then play the note to create 'swarm music'. 

## Contributors

- [Carlos Silveira](https://carlossilveiradesign.gitbook.io/mdef-diary): Code for playing notes and OpenAI integration and modeling for carapace 
- [Flavio Grimaldi](https://flavio-grimaldi-students-iaac.gitbook.io/mdef_flavio_grimaldi): Code for playing notes, sensing environment, and OpenAI integration 
- [Lucretia Field](https://lkfield.github.io/mdef/): Code for MQTT protocol and integration with OpenAI code 

---

##  Repository Structure

```sh
└── micro-swarm.git/
    ├── BarduinoAI
    │   ├── AIController.cpp
    │   ├── AIController.h
    │   ├── BarduinoAI.ino
    │   ├── Config.cpp
    │   ├── Config.h
    │   ├── FunctionRegistry.cpp
    │   ├── FunctionRegistry.h
    │   └── pitches.h
    ├── Input_Notes
    │   ├── Input_Notes.ino
    │   └── pitches.h
    ├── Piezo_Sensor
    │   ├── Piezo_Sensor.ino
    │   └── pitches.h
    ├── MQTTsend - Obsolete 
    │   ├── MQTTsend.ino
    │   ├── Config.cpp
    │   └── Config.h
    ├── MQTTreceive - Obsolete
    │   ├── MQTTreceive.ino
    │   ├── Config.cpp
    │   └── Config.h
    ├── mqtt_reference - Current 
    │   ├── mqtt_reference.ino
    │   ├── Config.cpp
    │   └── Config.h
    ├── mqtt_cell1 - Current
    │   ├── mqtt_cell1.ino
    │   ├── Config.cpp
    │   └── Config.h
    ├── mqtt_ref_call - Current (MQTT Reference as Class )
    │   ├── mqtt_ref_call.ino
    │   ├── mqtt_reference.cpp
    │   ├── mqtt_reference.h
    │   ├── Config.cpp
    │   ├── Config.h
    │   └── pitches.h
    └── README.md
```
---

## Fabrication Process 
### The System Structure 

The proposed system is composed of a single "Mother" or "Reference" device that reads an input from a sensor and sends out a signal to the "Child" or "Cell" nodes to make certain noises in response to the stimuli. 

The Reference node will process the input from a sensor to determine the frequency of a note to play on the onboard piezo buzzer while simultaneously sending a query to an ChatGPT prompt through the OpenAI API to determine harmonizing frequencies for the desired note. The information of the harmonizing note is then conveyed to the Cell nodes using Message Queues Telemetry Transport (MQTT) publish-subscribe protocol on a local WiFi network through an existing MQTT broker server. When the Cells receive the frequency, they will activate the onboard buzzers to play the sound, creating the harmonious din of cicadas. 

#### Mother/Reference

When a predator makes a vibration close to the Mother node, the node will send out a "danger" signal so that the Children nodes are alerted. A predator's approach is detected through a piezo vibration sensor on the Reference device. When the sensed vibration is within an acceptable range, to cut out noise from the sensor, the value is mapped to correspond to one of the indexes of 88 notes which is passed to the OpenAI prompt. The prompt requests that 3 harmonizing notes be determined from the given note and returns them as an array. 

The Reference node will then relay a different frequency to each of the Cells so they can respond in an individualist manner to make sure all of the children heard the call. This is done by publishing the desired frequency to a different 'topic' to which the Cells can each subscribe to receive only the frequency meant for their buzzer. 

#### The Children/Cells

The code for the cells are much simpler. Each Cell subscribes to a topic and then when a new message comes in from the Reference, plug that value in to the buzzer frequency and play the note. 

### The Carapace 

The carapace, with an insect look, besides being designed to be adpatable in its internal parts when assembling the electronic components to improve time, for mother and son, it was intentionally designed to reverbarate the acoustic from one chamber to the other and amplify the sound emited by the buzzer inside of the artificial insect. The structure of the arctifact is divided in two specific parts, a flexible silicone base with four legs that can be attached to different places vertically and horizontally with sucktion cups on each leg, and an external strcuture that covers the Barduino board, battery and piezo sensor, 3D printed in PLA to protect the componentes from the external interference and maximize the sound by using oval shapes and seven holes on top to let the air flow from the chamber to the outside. 

To produce, the carapace was used a a Bamboo 3D printer for the shell, a Creality Ender to print the molld for the silicone bottom layer, and Blender and Adobe Illustrator the to define the shapes and forms. It's important to enhance the several changes made during the project that trasnformed the original shaped to a new version considering the possibilities of batteries to be used on the Barduino and they would be distribute insied of the carapace withou interfering each other, what consequently gave a more anaphormical shape specifically designed to the board and components for this Micro Challenge.


### Iteration Process 

Flavio schematics


---

## Reference Projects/Inspiration 

Cigars, Birds, 


---

## Future Project Developments 

Lucretia: From the beginning we were interested in exploring different inputs to the system, for a future iteration of the project, we think it would be very cool to have the potential for the input to come from a MIDI controller where a human could provide a note or series of notes for the 'cicadas' to harmonize with. Instead of mimicking a danger sense in animals in nature, this functionality could allow the human and the 'insects' to work together to create a musical atmosphere.

Carlos: Considering the logical nature of the communication between different individuals in a swarm, this project could truly be used to aware an sense enviromental issues, as something camouflaged in nature giving signs to humans and other animals. One of the possibilities that I would like to explore is trying to mimick the frequencies of specific livings beings to communicate and create an artifical-biological relation to trigger actions, this would have a truly potentional to enviromental measurament and care and coube be used in different biomes with easy adaptabillity. In addition, this could would provied a glimpse of the possibilities to communicate different individuals with one reference of control, something that could truly be applied to my research in biohybrid robots, and at lastm, it would be delighful to improve and give AI autonomy to each one of the robots.

Flavio:


---

##  License

This project is protected under the [MIT LICENSE](https://en.wikipedia.org/wiki/MIT_License) License. For more details, refer to the [LICENSE](/LICENSE) file.

---

##  Acknowledgments

- Code cloned from Extended Intelligences [MDEF Repo](https://github.com/matta-pie/MDEF)
- References from [Sending Data over MQTT](https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device/).
- We had a lot of help from teachers at IAAC and Fab Lab BCN 
- This program is a joint Masters between IAAC, Fab Lab BCN, and Elisava 

---