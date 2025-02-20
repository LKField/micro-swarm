<p align="center">
    <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" align="center" width="30%">
</p>
<p align="center"><h1 align="center">MDEF.GIT</h1></p>
<p align="center">
	<em>Innovate, Connect, Automate: Code Your Future</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/matta-pie/MDEF.git?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/matta-pie/MDEF.git?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/matta-pie/MDEF.git?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/matta-pie/MDEF.git?style=default&color=0080ff" alt="repo-language-count">
</p>
<p align="center"><!-- default option, no dependency badges. -->
</p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>
<br>

##  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Project Structure](#-project-structure)
  - [ Project Index](#-project-index)
- [ Getting Started](#-getting-started)
  - [ Prerequisites](#-prerequisites)
  - [ Installation](#-installation)
  - [ Usage](#-usage)
  - [ Testing](#-testing)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview

MDEF.git simplifies managing functions and configurations in Arduino and ESP32 projects. It streamlines function registration and centralizes critical settings for WiFi, OpenAI, and hardware components. Ideal for developers creating smart home systems or AI camera applications, it enhances code organization and accessibility, fostering efficient project maintenance.

---

##  Features

|      | Feature         | Summary       |
| :--- | :---:           | :---          |
| ⚙️  | **Architecture**  | <ul><li>**Key Components:** `Arduino`, `ESP32`, `OpenAI`</li><li>**Microcontroller-based:** Utilizes Arduino and ESP32 for hardware interaction</li><li>**Modular Design:** Separation of concerns with distinct components for AI, WiFi, and hardware control</li><li>**Event-Driven:** Utilizes event-based architecture for sensor readings and AI responses</li></ul> |
| 🔩 | **Code Quality**  | <ul><li>**Consistent Coding Standards:** Follows consistent coding standards across files</li><li>**Modular Codebase:** Encourages code reusability and maintainability through modular design</li><li>**Comments and Documentation:** Well-documented codebase with clear comments for functions and classes</li></ul> |
| 📄 | **Documentation** | <ul><li>**Primary Language:** `C`</li><li>**Language Distribution:** `h` (9), `ino` (2), `cpp` (6)</li><li>**Detailed File Descriptions:** Provides detailed descriptions for each file, outlining their purpose and functionality</li></ul> |
| 🔌 | **Integrations**  | <ul><li>**OpenAI Integration:** Utilizes OpenAI's GPT models for AI interactions</li><li>**WiFi Connectivity:** Establishes secure WiFi connections for data transmission</li><li>**Hardware Integration:** Interacts with hardware components like sensors, LEDs, and cameras</li></ul> |
| 🧩 | **Modularity**    | <ul><li>**Component-based Design:** Separates functionality into distinct components for easier maintenance</li><li>**Function Registry:** Manages dynamic functions with attachment and retrieval capabilities</li><li>**Configuration Centralization:** Centralizes critical settings for WiFi, OpenAI, and hardware components</li></ul> |
| 🧪 | **Testing**       | <ul><li>**Test Commands:** Provides commands for testing functionalities within the project</li><li>**Testable Components:** Components designed for easy testing and verification</li><li>**Unit Testing:** Supports unit testing for critical functionalities</li></ul> |
| ⚡️  | **Performance**   | <ul><li>**Efficient Image Processing:** Optimizes image processing for AI interactions</li><li>**Low Latency:** Minimizes latency in sensor readings and AI responses</li><li>**Resource Management:** Efficiently manages resources for optimal performance</li></ul> |
| 🛡️ | **Security**      | <ul><li>**Secure API Calls:** Ensures secure API calls with limitations to prevent abuse</li><li>**WiFi Security:** Implements secure WiFi connections for data transmission</li><li>**Configuration Security:** Safeguards critical configurations for network and AI interactions</li></ul> |

---

##  Project Structure

```sh
└── MDEF.git/
    ├── BarduinoAI
    │   ├── AIController.cpp
    │   ├── AIController.h
    │   ├── BarduinoAI.ino
    │   ├── Config.cpp
    │   ├── Config.h
    │   ├── FunctionRegistry.cpp
    │   ├── FunctionRegistry.h
    │   └── pitches.h
    ├── ESP32CamAI
    │   ├── AIController.cpp
    │   ├── AIController.h
    │   ├── CameraSetup.h
    │   ├── Config.cpp
    │   ├── Config.h
    │   ├── DisplaySetup.h
    │   ├── ESP32CamAI.ino
    │   ├── FunctionRegistry.cpp
    │   └── FunctionRegistry.h
    └── README.md
```


###  Project Index
<details open>
	<summary><b><code>MDEF.GIT/</code></b></summary>
	<details> <!-- __root__ Submodule -->
		<summary><b>__root__</b></summary>
		<blockquote>
			<table>
			</table>
		</blockquote>
	</details>
	<details> <!-- BarduinoAI Submodule -->
		<summary><b>BarduinoAI</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/FunctionRegistry.h'>FunctionRegistry.h</a></b></td>
				<td>- Manages a registry of functions with names and pointers, allowing attachment and retrieval<br>- Supports a maximum of 10 functions and provides methods to list names, count functions, and generate a bulleted list.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/Config.h'>Config.h</a></b></td>
				<td>- Centralize configuration settings for WiFi, OpenAI, and hardware components<br>- Define static values for SSID, passwords, API keys, and pin mappings<br>- Facilitate easy access and modification of critical parameters across the codebase.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/BarduinoAI.ino'>BarduinoAI.ino</a></b></td>
				<td>- Implements a smart home system on an Arduino board, integrating sensors for light and temperature readings, LED control, and a buzzer<br>- Connects to WiFi for AI processing and response handling<br>- The system captures sensor data, processes it with AI, and executes corresponding actions based on the AI response.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/AIController.cpp'>AIController.cpp</a></b></td>
				<td>- Facilitates AI interaction by processing image and text data, leveraging OpenAI's GPT models<br>- Manages API calls, limiting them to prevent exceeding thresholds<br>- Constructs prompts based on input data and available actions, enhancing conversational capabilities<br>- Maintains a count of successful calls to regulate usage.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/FunctionRegistry.cpp'>FunctionRegistry.cpp</a></b></td>
				<td>- Manage and store functions for dynamic invocation within the project<br>- Allows attaching, retrieving, and counting functions by name<br>- Provides a list of available functions in a formatted manner.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/AIController.h'>AIController.h</a></b></td>
				<td>- Handles AI-related operations by processing image and text data using ChatGPT and interacting with a secure WiFi client<br>- Tracks successful API calls and provides results based on available actions.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/Config.cpp'>Config.cpp</a></b></td>
				<td>- Defines configurations for WiFi, OpenAI, and hardware pins used in the project<br>- Centralizes essential settings for network, AI model, and hardware components<br>- Organizes key parameters for seamless integration and easy maintenance across the codebase architecture.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/BarduinoAI/pitches.h'>pitches.h</a></b></td>
				<td>- Defines musical note frequencies for various octaves, facilitating sound generation in the project<br>- This file centralizes constants for notes ranging from B0 to D8, enabling easy reference and usage throughout the codebase.</td>
			</tr>
			</table>
		</blockquote>
	</details>
	<details> <!-- ESP32CamAI Submodule -->
		<summary><b>ESP32CamAI</b></summary>
		<blockquote>
			<table>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/ESP32CamAI.ino'>ESP32CamAI.ino</a></b></td>
				<td>- Implements the core functionality for an ESP32-based AI camera system<br>- Handles camera initialization, image processing, AI interaction, and LED control<br>- Establishes network connectivity, registers functions, and orchestrates AI responses<br>- Facilitates seamless image capture, processing, and AI feedback loop for the project's AI camera application.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/FunctionRegistry.h'>FunctionRegistry.h</a></b></td>
				<td>- Manages a registry of functions with names and pointers, allowing attachment and retrieval<br>- Supports a maximum of 10 functions<br>- Provides methods to attach functions, retrieve function names, find functions by name, and get a bulleted list of all functions.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/Config.h'>Config.h</a></b></td>
				<td>- Central configuration for WiFi, OpenAI, and hardware pins<br>- Defines static values for WiFi SSID and password, OpenAI API key, model, call limits, tokens, prompts, and hardware pin assignments<br>- Organizes key settings in a structured manner for easy access and modification across the codebase.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/AIController.cpp'>AIController.cpp</a></b></td>
				<td>- Handles AI interactions by processing image and text data, utilizing OpenAI's GPT model<br>- Manages API calls, ensuring a limit on successful requests<br>- Constructs prompts based on input data and available actions, facilitating meaningful interactions with the AI model.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/FunctionRegistry.cpp'>FunctionRegistry.cpp</a></b></td>
				<td>- Manages a registry of functions, allowing attachment, retrieval by name, and listing of function names<br>- This component facilitates dynamic function handling within the project architecture.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/CameraSetup.h'>CameraSetup.h</a></b></td>
				<td>- Enables camera initialization and converts image frames to Base64 encoding with a JPEG format prefix<br>- The code defines pin assignments and camera settings, then initializes the camera module<br>- Additionally, it encodes the frame buffer to Base64 format for image transmission.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/AIController.h'>AIController.h</a></b></td>
				<td>- Handles AI-related operations by processing image and text data using ChatGPT<br>- The AIController class encapsulates functionality for interacting with AI models, leveraging WiFiClientSecure for secure communication<br>- It manages successful API calls and integrates with the project's configuration settings.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/Config.cpp'>Config.cpp</a></b></td>
				<td>- Defines configurations for WiFi, OpenAI, and hardware in the project<br>- Specifies SSID, password, API key, model, call limits, tokens, base prompt, and goal<br>- Also sets the onboard LED pin<br>- This file centralizes key settings for network, AI, and hardware components, facilitating easy management and modification of these parameters across the codebase architecture.</td>
			</tr>
			<tr>
				<td><b><a href='https://github.com/matta-pie/MDEF.git/blob/master/ESP32CamAI/DisplaySetup.h'>DisplaySetup.h</a></b></td>
				<td>- Enables OLED display setup and management for ESP32-CAM, ensuring seamless integration with defined I2C pins<br>- Facilitates text display and line clearing functionalities, enhancing user interaction and visual feedback within the project architecture.</td>
			</tr>
			</table>
		</blockquote>
	</details>
</details>

---
##  Getting Started

###  Prerequisites

Before getting started with MDEF.git, ensure your runtime environment meets the following requirements:

- **Programming Language:** C


###  Installation

Install MDEF.git using one of the following methods:

**Build from source:**

1. Clone the MDEF.git repository:
```sh
❯ git clone https://github.com/matta-pie/MDEF.git
```

2. Navigate to the project directory:
```sh
❯ cd MDEF.git
```

3. Install the project dependencies:

echo 'INSERT-INSTALL-COMMAND-HERE'



###  Usage
Run MDEF.git using the following command:
echo 'INSERT-RUN-COMMAND-HERE'

###  Testing
Run the test suite using the following command:
echo 'INSERT-TEST-COMMAND-HERE'

---
##  Project Roadmap

- [X] **`Task 1`**: <strike>Implement feature one.</strike>
- [ ] **`Task 2`**: Implement feature two.
- [ ] **`Task 3`**: Implement feature three.

---

##  Contributing

- **💬 [Join the Discussions](https://github.com/matta-pie/MDEF.git/discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://github.com/matta-pie/MDEF.git/issues)**: Submit bugs found or log feature requests for the `MDEF.git` project.
- **💡 [Submit Pull Requests](https://github.com/matta-pie/MDEF.git/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/matta-pie/MDEF.git
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/matta-pie/MDEF.git/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=matta-pie/MDEF.git">
   </a>
</p>
</details>

---

##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- List any resources, contributors, inspiration, etc. here.

---
