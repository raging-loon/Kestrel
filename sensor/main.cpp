#include <cstdio>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <libkds/kds_mod.h>
int main(int argc, char** argv)
{
    printf("hello\n");

    YAML::Node config = YAML::LoadFile("data/sensor_cfg.yml");
    std::cout << config["interfaces"].size() << std::endl;;
    for(const auto& iface : config["interfaces"]) 
    {
        for(const auto& kv : iface) 
        {
            std::cout << kv.first.as<std::string>() << std::endl;
        }
    }
    
    return 0;
}