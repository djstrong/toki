#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>

class Config
{
public:
	Config();


private:
	std::map<std::string, std::string> dict_;
};

#endif // CONFIG_H
