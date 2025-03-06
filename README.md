# Micro Swarm 

##  Overview

Micro Swarm is a project for the MDEF01 2024-2025 Course to test 'swarm intelligence' using a series of [Barduino (ESP32)](https://fablabbcn-projects.gitlab.io/electronics/barduino-docs/) devices. With an input from a human user (vibration sensor), a note will be played on a single 'reference' device. Using OpenAI, a harmonizing note or melody will be determined and relayed to the 'cell' devices via MQTT. The 'cell' devices will then play the note/melody to create 'swarm music'. 

This is a project by [Carlos Silveira](https://carlossilveiradesign.gitbook.io/mdef-diary), [Flavio Grimaldi](https://flavio-grimaldi-students-iaac.gitbook.io/mdef_flavio_grimaldi), and [Lucretia Field](https://lkfield.github.io/mdef/). 


The diagram system 

Mother/Reference

The human/danger is making a vibration close to the mother. The device through a piezo sensor detect the vibrations and send it to OpenAi only when the vibration is into a certain range value. When the  one number related to a note will be sent to OpenAi, which it will have the goal of send back three harmonized notes in terms of index to the serial monitor. 
The next step has been to send the notes to the relative cells to produce harmonized sounds on the buzzer. 






The sons/Cells







---

##  Project Structure

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
    └── README.md
```

##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- Code cloned from Extended Intelligences [MDEF Repo](https://github.com/matta-pie/MDEF)
- References from [Sending Data over MQTT](https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device/).


---