#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_


class ConfigurationManager {
private:
public:
	ConfigurationManager(const char* configurationPath);
		virtual ~ConfigurationManager();
};

#endif /* CONFIGURATIONMANAGER_H_ */
