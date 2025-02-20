#include "Arduino.h"
#include "FunctionRegistry.h"

FunctionRegistry::FunctionRegistry() : functionCount(0) {
  // You can initialize the registry array if needed.
  for (int i = 0; i < MAX_FUNCTIONS; i++) {
    registry[i].name = "";
    registry[i].func = 0;
  }
}

bool FunctionRegistry::attachFunction(String name, FuncPtr func) {
  // Ensure we have room to attach a new function
  if (functionCount >= MAX_FUNCTIONS) {
    return false;
  }
  
  // Add the function info to the registry
  registry[functionCount].name = name;
  registry[functionCount].func = func;
  functionCount++;
  return true;
}

int FunctionRegistry::getFunctionNames(String names[]) {
  for (int i = 0; i < functionCount; i++) {
    names[i] = registry[i].name;
  }
  // Return the number of functions copied.
  return functionCount;
}

FunctionRegistry::FuncPtr FunctionRegistry::getFunctionByName(String name) {
  for (int i = 0; i < functionCount; i++) {
    if (registry[i].name == name) {
      return registry[i].func;
    }
  }
  // Return NULL if not found.
  return 0;
}

int FunctionRegistry::getFunctionCount() {
  return functionCount;
}

String FunctionRegistry::getBulletList() {
  String list = "";
  for (int i = 0; i < functionCount; i++) {
    // Add a bullet point and the function name followed by a newline.
    list += "- " + registry[i].name + "\\n";
  }
  return list;
}