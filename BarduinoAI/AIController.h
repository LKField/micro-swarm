// AIController.h - Handles AI-related operations
#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <ChatGPT.hpp>
#include "config.h"

class AIController {
  public:
      AIController(WiFiClientSecure& client);
      bool processImage(const char* base64Image, const String& availableActions, String& result);
      bool processTextData(const String& inputData, const String& availableActions, String& result);
      bool processNotes(const String& inputData, String& result);


  private:
      ChatGPT<WiFiClientSecure> chatGPT;
      int successfulCalls;
};

#endif