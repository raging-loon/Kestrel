#include <cstdio>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>
#include <libkds/kds_mod.h>
#include "DataSource.h"

int main(int argc, char** argv)
{
    printf("hello\n");

    // YAML::Node config = YAML::LoadFile("data/sensor_cfg.yml");
    // std::cout << config["interfaces"].size() << std::endl;;
    // for(const auto& iface : config["interfaces"]) 
    // {
    //     for(const auto& kv : iface) 
    //     {
    //         std::cout << kv.first.as<std::string>() << std::endl;
    //     }
    // }


    kestrel::DataSource ds;

    if(ds.loadModule("build/kds_pcap.so") != KDS_OK)
        printf("faile !\n");
    
    auto dsh = ds.createHandle();

    kds_error status = dsh->prepareHandle();

    if(status == KDS_OK)
        printf("ok\n");
    return 0;
}