#ifndef CONFIGOPER_H
#define CONFIGOPER_H
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
#include<assert.h>

enum class ConfigWriteType
{
    Cover=0,
    Append
};

class ConfigOper
{
private:
    static std::string SERVER_CONFIG_PATH;
public:
    ConfigOper();
    ~ConfigOper();

    static std::unordered_map<std::string, std::string> ReadConfig(std::string configPath);
    static bool WriteConfig(std::string configPath, std::unordered_map<std::string, std::string>& configmap, ConfigWriteType writeType);
    static bool WriteConfig(std::string configPath, std::string fieldName, std::string fieldValue);


};

#endif
