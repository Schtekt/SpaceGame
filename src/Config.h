#ifndef CONFIG_H
#define CONFIG_H
#include <string>
/*
This class holds all the configurations for the game(ex. window size)
The class is a singleton to access its values wherever in the code.
*/
class Config {
private:
	//Init
	Config();
	//Other
	int m_windowWidth;
	int m_windowHeight;

	int getVariableID(std::string str);
public:
	//Singleton Settings
	Config(Config const&) = delete;
	void operator=(Config const&) = delete;

	static Config& getInstance() 
	{
		static Config instance;
		return instance;
	}
	//Other
	int getWindowSizeWidth();
	int getWindowSizeHeight();
};

#endif // !CONFIG_H
