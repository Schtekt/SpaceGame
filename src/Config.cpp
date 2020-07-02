#include "Config.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
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

			switch (GetVariableID(variable)) {
			case WINDOW_HEIGHT:
				m_WindowHeight = std::stoi(value);
				break;
			case WINDOW_WIDTH:
				m_WindowWidth = std::stoi(value);
				break;
			default:
				std::cout << "Unknown variable \"" << variable << "\" with value \"" << value << "\"";
				break;
			}
		}
	}
}

int Config::GetVariableID(std::string str)
{
	if (std::strcmp(str.c_str(), "windowSizeWidth") == 0) return WINDOW_WIDTH;
	if (std::strcmp(str.c_str(), "windowSizeHeight") == 0) return WINDOW_HEIGHT;

	return INVALID;
}

int Config::GetWindowSizeWidth()
{
	return m_WindowWidth;
}

int Config::GetWindowSizeHeight()
{
	return m_WindowHeight;
}
