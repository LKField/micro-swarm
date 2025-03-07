// AIController.cpp
#include "AIController.h"

AIController::AIController(WiFiClientSecure& client) 
    : chatGPT(&client, "v1", OpenAIConfig::API_KEY, 60000)
    , successfulCalls(0) {
}

bool AIController::processImage(const char* base64Image, const String& availableActions, String& result) {
    if (successfulCalls >= OpenAIConfig::MAX_CALLS) {
        return false;
    }

    String prompt = String(OpenAIConfig::BASE_PROMPT) + 
                   String(OpenAIConfig::GOAL) + 
                   "Actions: \\n" + availableActions;

    bool success = chatGPT.vision_question(
        OpenAIConfig::MODEL,
        "user",
        "text",
        prompt.c_str(),
        "image_url",
        base64Image,
        "low",
        OpenAIConfig::MAX_TOKENS,
        true,
        result
    );

    if (success) {
        successfulCalls++;
    }

    return success;
}

bool AIController::processTextData(const String& inputData, const String& availableActions, String& result) {
  if (successfulCalls >= OpenAIConfig::MAX_CALLS) {
      return false;
  }
  String prompt = String(OpenAIConfig::GOAL) + inputData;

  Serial.println(prompt);

  bool success = chatGPT.chat_message(
    OpenAIConfig::MODEL, 
    "user", 
    prompt.c_str(), 
    OpenAIConfig::MAX_TOKENS, 
    true, 
    result, 
    true
  );

  if (success) {
      successfulCalls++;
  }

  return success;
}
bool AIController::processNotes(const String& inputData, String& result) {

  if (successfulCalls >= OpenAIConfig::MAX_CALLS) {
        return false;
    }
    String prompt = String(OpenAIConfig::GOAL) + inputData;

    Serial.println(prompt);

    bool message = chatGPT.chat_message(
      OpenAIConfig::MODEL, 
      "user", 
      prompt.c_str(), 
      OpenAIConfig::MAX_TOKENS, 
      true, 
      result, 
      true
    );

    if (message) {
      successfulCalls++;
      Serial.println("API call successful: " + result);
    } else {
      result = "Error: Failed to get response from OpenAI API";
      Serial.println(result);
    }

    return message;
}