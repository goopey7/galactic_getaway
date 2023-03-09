﻿#include "InputActionManager.h"
#include <fstream>
#include <input/keyboard.h>

InputActionManager::InputActionManager()
{
	// initialize actions vector from string
	initializeActions(actionsStr);

	// TODO handle error if file not found
	
	// read bindings.json in config folder
	std::ifstream i("config/bindings.json");

	// parse json into cpp object
	bindingsJson = json::parse(i);

	// setup action bindings
	for(auto keyboardBinding : bindingsJson["keyboard"])
	{
		actionBindings[stringToAction[keyboardBinding["action"]]] = keyboardBinding["key"];
	}
}

void InputActionManager::handleInputEvents()
{
}

void InputActionManager::initializeActions(const char* values)
{
	// parse string into vector of strings on the commas
	for(int i = 0; values[i] != '\0'; i++) {
		if(values[i] == ',') {
			actions.push_back(std::string(values, i));
			values = values + i + 1;
			i = -1;
		}
	}
	actions.push_back(values);

	// clear up spaces
	for(int i = 0; i < actions.size(); i++)
	{
		if(actions[i][0] == ' ')
		{
			actions[i] = actions[i].substr(1);
		}

		// setup string to action map for easy lookup
		stringToAction[actions[i]] = (Action)i;
	}
}
