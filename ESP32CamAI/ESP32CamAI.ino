#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ChatGPT.hpp>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"

// Include the file with the camera setup config
#include "CameraSetup.h" 

// Include the file with the OLED display setup config
#include "DisplaySetup.h" 

// Include the utility to allow the AI to chose a function to execute
#include "FunctionRegistry.h"

// Create an instance of the registry.
FunctionRegistry funcRegistry;

// Wifi connection
const char* ssid = "********";
const char* password = "********";

WiFiClientSecure client;

// OpenAI API-Key
#define OPEN_AI_MAX_CALLS 3
#define OPEN_AI_MAX_TOKENS 2000
int successful_open_ai_calls = 0;
static const char *open_ai_key = "********";
static const char *open_ai_model = "gpt-4o-mini";
ChatGPT<WiFiClientSecure> chatGPT_Client(&client, "v1", open_ai_key, 60000);

// OpenAI Prompt
const String BASE_PROMPT = "You are an automata with a goal and a list of actions that you can execute to achieve that goal. \\n" 
                            "On each iteration you will receive an image, you analize the image and return the action that is most probable to make you achieve your goal. \\n"
                            "Return the action in plain text, without any additional symbols or explanation. \\n";

const String GOAL = "Goal: shine light whenever you see a pair of scissors. \\n";

// Onboard LED
#define ONBOARD_LED 4

// Define my custom functions here
void turn_on_led() {
  digitalWrite (ONBOARD_LED, HIGH);
}

void turn_off_led() {
  digitalWrite (ONBOARD_LED, LOW);
}

void setup() {
  Serial.begin(115200);

  setupDisplay();

  // Initialize Camera module
  esp_err_t err = initCameraModule();
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    while (true) { delay(1000); }  // Stop execution if initialization fails
  }
  Serial.println("Camera initialized successfully");

  // Initialize WiFi connection
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  // Wait until we get a wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    printOLED(0, "Connecting...");
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());

  printOLED(0, WiFi.localIP().toString());

  // Ignore SSL certificate validation
  client.setInsecure();

  // Set led pin as output
  pinMode(ONBOARD_LED, OUTPUT);

  // Attach the functions to teh registry
  funcRegistry.attachFunction("TURN_ON_LED", turn_on_led);
  funcRegistry.attachFunction("TURN_OFF_LED", turn_off_led);
}

void loop() {
  while(successful_open_ai_calls >= OPEN_AI_MAX_CALLS) { /* spin and do nothing */ } 
  
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    return;
  }
  
  // Convert the captured image to Base64
  char* base64ImageData = fbToBase64(fb);

  // Return the frame buffer when finished (IMPORTANT)
  esp_camera_fb_return(fb);

  String actions = "Actions: \\n" + funcRegistry.getBulletList();
  String prompt = BASE_PROMPT + GOAL + actions;
  const char* prompt_chars = prompt.c_str();

  String result;
  Serial.println("\n\n[ChatGPT] - Asking a Vision Question");
  Serial.println(prompt_chars);
  
  printOLED(4, "Asking OpenAI...");

  if (chatGPT_Client.vision_question(open_ai_model, "user", "text", prompt_chars, "image_url", base64ImageData, "low", OPEN_AI_MAX_TOKENS, true, result)) {
    Serial.print("[ChatGPT] Response: ");
    Serial.println(result);
    printOLED(4, result);
    successful_open_ai_calls++;
    FunctionRegistry::FuncPtr f = funcRegistry.getFunctionByName(result);
    if (f) {
      f();
    }
  } else {
    Serial.print("[ChatGPT] Error: ");
    Serial.println(result);
    printOLED(4, "< Error >");
  }

  delay(5000);
}
