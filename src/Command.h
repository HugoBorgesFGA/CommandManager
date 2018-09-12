#ifndef INC_MODEL_COMMAND_H_
#define INC_MODEL_COMMAND_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#define COMMAND_E_SUCCESSFULL 0

class Command {
protected:
	bool containsNestedKey(const JsonObject& obj, const char* key);

public:
	virtual unsigned int exec(JsonObject& input, JsonObject& output) = 0;
	~Command(){};
};


#endif
