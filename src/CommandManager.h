#ifndef INC_MODEL_COMMAND_MANAGER_H_
#define INC_MODEL_COMMAND_MANAGER_H_

#include "ArduinoJson.h"
#include "Command.h"

class CommandManager
{
private:
	Command *getCommandByName(const char *methodName);

public:
	CommandManager();
	~CommandManager();

	void parse(char *input);
};

#endif
