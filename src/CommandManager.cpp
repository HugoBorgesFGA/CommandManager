#include "CommandManager.h"

#include <Arduino.h>
#include "string.h"

CommandManager::CommandManager()
{

};

CommandManager::~CommandManager()
{

};

/*
 * Command Factory.
 *
 * Returns the command associated to the required methodName
 */
Command *CommandManager::getCommandByName(const char *methodName)
{

	return nullptr;
}

void CommandManager::parse(char *input)
{
	const char *methodName;
	StaticJsonBuffer<192> jsonInputBuffer;
	StaticJsonBuffer<192> jsonOutputBuffer;

	jsonInputBuffer.clear();
	jsonOutputBuffer.clear();

	JsonObject& inputJson = jsonInputBuffer.parseObject(input);
	JsonObject& outputJson = jsonOutputBuffer.createObject();
	unsigned char error;
	Command *cmd = nullptr;

	// Is it a valid JSON?
	if (!inputJson.success()) {
		outputJson["err"] = 7;

		Serial.print("Received: ");
		Serial.println(input);

		goto out;
	}

	// Does it contains the method name?
	if (inputJson.containsKey("cmd") == false) {
		outputJson["err"] = 8;
		goto out;
	}

	methodName = inputJson["cmd"];
	cmd = this->getCommandByName(methodName);
	if (cmd == nullptr) {
		outputJson["err"] = 9;
		goto out;
	}

	outputJson["cmd"] = methodName;
	error = cmd->exec(inputJson, outputJson);
	if (error) {
		JsonObject& errorJson = jsonOutputBuffer.createObject();

		errorJson["cmd"] = methodName;
		errorJson["err"]  = error;

		errorJson.printTo(Serial);
		Serial.print('\n');
		return;
	}

	outputJson["err"] = error;

out:
	outputJson.printTo(Serial);
	Serial.print('\n');
}
