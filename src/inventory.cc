//
// Created by mauro on 1/16/20.
//

#include "inventory.h"

Inventory::Inventory(unsigned int timeout, char *apiKey) : timeout(timeout), api_key(apiKey) {
    if (getEnvVar("API_ADDR").empty()) {
        dcim_client_ = std::make_unique<httplib::SSLClient>("portal.isprime.com", 443, timeout);
        dcim_client_->set_read_timeout(timeout, 0);
    } else {
        dcim_client_ = std::make_unique<httplib::SSLClient>(getEnvVar("API_ADDR").c_str(), 443,
                                                            timeout);
        dcim_client_->set_read_timeout(timeout, 0);
    }
}

Inventory::~Inventory() {}

std::string Inventory::getEnvVar(std::string const &key) {
    char const *val = getenv(key.c_str());
    return val == nullptr ? std::string() : std::string(val);
}

void Inventory::buildInventory(std::string &query, std::string &filepath) {
    try {
        httplib::Headers headers {{"apikey", api_key}};

        auto res = dcim_client_->Get(query.c_str(), headers);

        if (res == nullptr) {
            cout << "easydcim response is nullptr, check your query: " << query.c_str() << endl;
            return;
        }
        rapidjson::Document document;
        if (res.get()) {
            // Parse the JSON
            if (document.ParseInsitu<0>((char *) res->body.c_str()).HasParseError()) {
                cout << res->body << endl;
                return;
            }
        }

        if (!document.IsObject()) {
            cout << "Easydcim does not returned an object" << endl;
            return;
        }

        if (document.HasMember("status")) {
            if (document["status"].IsString()) {
                if (document["status"].IsString()) {
                    auto status = document["status"].GetString();
                    if (strncmp(status, "success", 7) == 0) {
                        if (document.HasMember("result")) {
                            if (document["result"].IsArray()) {

                                rapidjson::StringBuffer sb;
                                rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
                                document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.

                                ofstream raw;
                                raw.open(filepath);
                                raw << sb.GetString();
                                raw.close();

                                const rapidjson::Value &result = document["result"]; // Using a reference for consecutive access is handy and faster.
                                cout << "API returned " << result.Size() << " results.\n" << endl;

                                for (rapidjson::SizeType i = 0; i < result.Size(); i++) {
                                    cout << "Label: " << result[i]["label"].GetString() << " IP Address: " << result[i]["metalist"]["IP Address"].GetString() << endl;
                                }

                            }
                        }
                    }
                }
            }
        }
    }
    catch (std::exception &e) {
        cout << "error: " << e.what() << endl;
    }
}