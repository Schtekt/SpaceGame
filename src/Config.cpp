#include "Config.h"
#include <fstream>
#include <iostream>

enum {
	INVALID,
	WINDOW_HEIGHT,
	WINDOW_WIDTH
};

Config::Config()
{
	std::ifstream file("..//resources//config.txt");

	if (file.is_open()) {
		while (!file.eof()) {
			std::string variable;
			std::string value;
			std::getline(file, variable, '=');
			variable.erase(std::remove_if(variable.begin(), variable.end(), std::isspace));
			std::getline(file, value);

			switch (getVariableID(variable)) {
			case WINDOW_HEIGHT:
				m_windowHeight = std::stoi(value);
				break;
			case WINDOW_WIDTH:
				m_windowWidth = std::stoi(value);
				break;
			default:
				std::cout << "Unknown variable \"" << variable << "\" with value \"" << value << "\"";
				break;
			}
		}
	}
}

int Config::getVariableID(std::string str)
{
	if (std::strcmp(str.c_str(), "windowSizeWidth") == 0) return WINDOW_WIDTH;
	if (std::strcmp(str.c_str(), "windowSizeHeight") == 0) return WINDOW_HEIGHT;

	return INVALID;
}

int Config::getWindowSizeWidth()
{
	return m_windowWidth;
}

int Config::getWindowSizeHeight()
{
	return m_windowHeight;
}
