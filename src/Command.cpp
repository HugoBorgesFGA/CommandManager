#include "model/commands/command.h"

bool Command::containsNestedKey(const JsonObject& obj, const char* key)
{
	for (const JsonPair& pair : obj) {
		if (!strcmp(pair.key, key))
			return true;

		if (containsNestedKey(pair.value.as<JsonObject>(), key))
			return true;
	}

	return false;
}
