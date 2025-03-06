# Micro Swarm 

##  Overview

Micro Swarm is a project for the MDEF01 2024-2025 Course to test 'swarm intelligence' using a series of [Barduino (ESP32)](https://fablabbcn-projects.gitlab.io/electronics/barduino-docs/) devices. With an input from a human user (vibration sensor), a note will be played on a single 'reference' device. Using OpenAI, a harmonizing note or melody will be determined and relayed to the 'cell' devices via MQTT. The 'cell' devices will then play the note/melody to create 'swarm music'. 

This is a project by [Carlos Silveira](https://carlossilveiradesign.gitbook.io/mdef-diary), [Flavio Grimaldi](https://flavio-grimaldi-students-iaac.gitbook.io/mdef_flavio_grimaldi), and [Lucretia Field](https://lkfield.github.io/mdef/). 

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

## The System Structure 

The proposed system is composed of a single "Mother" or "Reference" device that reads an input from a sensor and sends out a signal to the "Child" or "Cell" nodes to make certain noises in response to the stimuli. 

The Reference node will process the input from a sensor to determine the frequency of a note to play on the onboard piezo buzzer while simultaneously sending a query to an ChatGPT prompt through the OpenAI API to determine harmonizing frequencies for the desired note. The information of the harmonizing note is then conveyed to the Cell nodes using Message Queues Telemetry Transport (MQTT) publish-subscribe protocol on a local WiFi network through an existing MQTT broker server. When the Cells receive the frequency, they will activate the onboard buzzers to play the sound, creating the harmonious din of cicadas. 

### Mother/Reference

When a predator makes a vibration close to the Mother node, the node will send out a "danger" signal so that the Children nodes are alerted. A predator's approach is detected through a piezo vibration sensor on the Reference device. When the sensed vibration is within an acceptable range, to cut out noise from the sensor, the value is mapped to correspond to one of the indexes of 88 notes which is passed to the OpenAI prompt. The prompt requests that 3 harmonizing notes be determined from the given note and returns them as an array. 

The Reference node will then relay a different frequency to each of the Cells so they can respond in an individualist manner to make sure all of the children heard the call. This is done by publishing the desired frequency to a different 'topic' to which the Cells can each subscribe to receive only the frequency meant for their buzzer. 

### The Children/Cells

The code for the cells are much simpler. Each Cell subscribes to a topic and then when a new message comes in from the Reference, plug that value in to the buzzer frequency and play the note. 

## The Carapace 



## Prototyping Process 



##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- Code cloned from Extended Intelligences [MDEF Repo](https://github.com/matta-pie/MDEF)
- References from [Sending Data over MQTT](https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device/).


---