#include "configOper.h"

ConfigOper::ConfigOper()
{
}

ConfigOper::~ConfigOper()
{
}

std::unordered_map<std::string, std::string> ConfigOper::ReadConfig(std::string configPath)
{
    std::ifstream in(configPath, std::ios::in);
    std::unordered_map<std::string, std::string> configMap;
    if (in.is_open()) {
        std::string line;
        while (getline(in, line)) {
            size_t index = line.find('=');
            configMap[line.substr(0, index)] = line.substr(index + 1);
        }
    }

    in.close();
    return configMap;
}

bool ConfigOper::WriteConfig(std::string configPath, std::unordered_map<std::string, std::string>& configmap, ConfigWriteType writeType)
{
    assert(!configPath.empty());
    std::ofstream out;
    if(ConfigWriteType::Cover == writeType)
    { 
        out.open(configPath, std::ios::out);
    }
    else if(ConfigWriteType::Append == writeType)
    {
        out.open(configPath, std::ios::out|std::ios::app);
    }

    if (out.is_open())
    {
        for (auto iter = configmap.begin(); iter != configmap.end(); iter++)
        {
            const char* fieldName = iter->first.c_str();
            const char* fieldValue = iter->second.c_str();
            out.write(fieldName, iter->first.length());
            out.write("=", 1);
            out.write(fieldValue, iter->second.length());
            out.write("\n", 1);
        }
    }
    
    out.close();
    return true;
}

bool ConfigOper::WriteConfig(std::string configPath, std::string fieldName, std::string fieldValue)
{
    assert(!configPath.empty());
    
    std::unordered_map<std::string, std::string> configMapTmp = ReadConfig(configPath);
    auto iter = configMapTmp.find(fieldName);
    if (iter != configMapTmp.end())
    {
        iter->second = fieldValue;
        return WriteConfig(configPath, configMapTmp, ConfigWriteType::Cover);;
    }
    return false;
}
