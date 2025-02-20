#ifndef FUNCTIONREGISTRY_H
#define FUNCTIONREGISTRY_H

#include "Arduino.h"

class FunctionRegistry {
public:
  // Define a function pointer type for functions with no arguments
  typedef String (*FuncPtr)(void);
  
  // Maximum number of functions that can be attached
  static const int MAX_FUNCTIONS = 10;
  
  // Constructor
  FunctionRegistry();

  // Attach a function along with a name.
  // Returns true if successfully attached, false if the registry is full.
  bool attachFunction(String name, FuncPtr func);

  // Copies the names of all attached functions into the provided array.
  // The caller should supply an array of String large enough (MAX_FUNCTIONS).
  // Returns the number of functions copied.
  int getFunctionNames(String names[]);

  // Given a function name, returns the attached function pointer.
  // Returns NULL (0) if not found.
  FuncPtr getFunctionByName(String name);

  // Optionally, get the total number of attached functions.
  int getFunctionCount();

  // Returns a single string containing bulletpoints of all functions.
  String getBulletList();
  
private:
  // Internal structure to hold the name and pointer.
  struct RegisteredFunction {
    String name;
    FuncPtr func;
  };

  RegisteredFunction registry[MAX_FUNCTIONS];
  int functionCount;
};

#endif