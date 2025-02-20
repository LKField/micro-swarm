// config.cpp
#include "Config.h"

// WiFi Configuration definitions
const char* WiFiConfig::SSID = "Iaac-Wifi";
const char* WiFiConfig::PASSWORD = "*****";

// OpenAI Configuration definitions
const char* OpenAIConfig::API_KEY = "*****";
const char* OpenAIConfig::MODEL = "gpt-4o-mini";
const int OpenAIConfig::MAX_CALLS = 3;
const int OpenAIConfig::MAX_TOKENS = 2000;
const char* OpenAIConfig::BASE_PROMPT = "You are an automata with a goal and a list of actions that you can execute to achieve that goal. \\\n"
                                      "On each iteration you will receive an image, you analyze the image and return the action that is most probable to make you achieve your goal. \\n"
                                      "Return the action in plain text, without any additional symbols or explanation. \\n";
const char* OpenAIConfig::GOAL = "Goal: turn on the light if there are people in the room, else turn the light off. \\n";

// Hardware Configuration definitions
const int PinConfig::ONBOARD_LED = 4;