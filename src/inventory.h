//
// Created by mauro on 1/16/20.
//

#pragma once

#define CPPHTTPLIB_OPENSSL_SUPPORT 1

#include <iostream>
#include <memory>
#include "httplib.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

using namespace std;

class Inventory {
private:
    std::unique_ptr<httplib::SSLClient> dcim_client_;
    std::string getEnvVar(std::string const &key);
    unsigned int timeout;
    char* api_key;
public:
    Inventory(unsigned int timeout, char *apiKey);

    virtual ~Inventory();

    void buildInventory(std::string &query, std::string &filepath);
};