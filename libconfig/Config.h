//
// Created by qiu on 2021/12/20.
//

#ifndef LIBCONFIG_CONFIG_H
#define LIBCONFIG_CONFIG_H
#include <yaml-cpp/yaml.h>
#include <string>
#include <cstring>
#include <utility>
#include <vector>
namespace libconfig {

    class Config {
    public:
        template<typename T>
        static T getConfig(std::string configname,T defaultValue)
        {
            try {
                auto conf = split(std::move(configname), ".");
                YAML::Node node = getData();
                for (auto &i: conf) {
                    node = node[i];
                }
                return node.as<T>();
            }catch (...)
            {
                return defaultValue;
            }
        }
        template<typename T>
        static std::vector<T> getConfig(std::string configname,std::vector<T> defaultValue)
        {
            try {
                auto conf = split(std::move(configname), ".");
                YAML::Node node = getData();
                for (auto &i: conf) {
                    node = node[i];
                }
                if(node.IsMap())
                {
                    std::vector<T> ret;
                    for(auto it=node.begin();it!=node.end();it++)
                    {
                        ret.push_back(it->first.template as<T>());
                    }
                    return ret;
                }
                if(node.size()==0) {
                    return {node.as<T>()};
                }
                return node.as<std::vector<T> >();
            }catch (...)
            {
                return defaultValue;
            }
        }



    private:
        static YAML::Node getData()
        {
            static YAML::Node data=YAML::LoadFile(getYamlConfigPath());
            //ToDo: don't return copy
            return Clone(data);
        }
        static std::string getYamlConfigPath()
        {
            std::string s(getenv("HOME"));
            s+="/.libconfig/config.yml";
            return s;
        }

        static std::vector<std::string> split(std::string str, const std::string& pattern)
        {
            std::string::size_type pos;
            std::vector<std::string> result;
            str += pattern;
            int size = str.size();
            for (int i = 0; i < size; i++)
            {
                pos = str.find(pattern, i);
                if (pos < size)
                {
                    std::string s = str.substr(i, pos - i);
                    result.push_back(s);
                    i = pos + pattern.size() - 1;
                }
            }
            return result;
        }
    };

#define GET_CONFIG(key,defaultValue) libconfig::Config::getConfig(key,defaultValue)
}

#endif //LIBCONFIG_CONFIG_H
