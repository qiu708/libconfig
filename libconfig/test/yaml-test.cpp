//
// Created by qiu on 2021/12/20.
//

#include <yaml-cpp/yaml.h>
#include<iostream>
#include <libconfig/Config.h>
using namespace std;
void printYaml(YAML::Node node)
{
    for(auto it=node.begin();it!=node.end();it++)
    {
        cout<<it->first.as<string>()<<endl;
    }

}
void templatetest()
{
//    std::cout<<libconfig::Config::getConfig("server.numthreads",int(2));
//    std::cout<<libconfig::Config::getConfig("server.numthreads",int(2));
//    std::cout<<libconfig::Config::getConfig("server.numthreads",int(2));
//    std::cout<<libconfig::Config::getConfig("server.numthreads",int(2));
//    cout<<libconfig::Config::getConfig("server.ip",string("hahaha"))<<endl;
    auto inst=libconfig::Config::getConfig("server.numthreads",std::vector<string>(1,"error"));
    auto inst2=GET_CONFIG("server.numthreads",std::vector<string>(1,"error"));
    for(auto s:inst2)
    {
        cout<<s<<"\n";
    }
}
int main()
{
    YAML::Node root=YAML::LoadFile("/home/qiu/Desktop/tmp/yamltemplate.yml");
    templatetest();
//    printYaml(root["server"]);
}