#ifndef SETTINGS_H
#define SETTINGS_H

class User_Setting
{
	User_Setting () : _screenWidth (1920), _screenheight (1080)
	public:
		int setDimensions (unsigned int x, unsigned int y);
		char* setGameFolder (const* char filePath);
		int setSaveFile (const* char filePath);
		int setConfigFile (const* char filePath);
		int setFPS (unsigned char fps);
		int setFOV (unsigned char fov);
		int setDifficulty (unsigned char difficulty);

		unsigned int getWidth ();
		unsigned int getHeight ();
		char* getSaveFile ();
		char* getConfigFile ();
		unsigned char getFPS ();
		unsigned char getFOV ();
		unsigned char getDifficulty ();

	private:
		// 200 min
		unsigned int _screenWidth, _screenHeight;
		std::string _saveFile;

		std::string _configFile;
		unsigned char _fps;
		// Angle 45 - 120
		unsigned char _fov;
		// ENUM?
		// 1 - God Mode		00
		// 2 - Easy			01
		// 3 - Medium		02
		// 4 - Default		03
		// 5 - Hard			04
		// 6 - Survival		05
		// 7 - Impossible	06
		// 8 - Debug		07
		unsigned char _difficulty;

};

#endif //SETTINGS_H
