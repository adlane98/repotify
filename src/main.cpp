#include <iostream>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"
#include "JsonReader.h"
#include "Domain.h"
#include <sys/stat.h>
#include <libnotify/notify.h>
#include <iomanip>
#include <typeinfo>


void show_notification(const char*, const char*);
void write_new_commit(const nlohmann::json&, const char*);
nlohmann::json make_request(const std::string& private_token);

int main() {
    JsonReader jr = JsonReader("../app_config.json");
    std::cout << std::setw(4) << jr.readJson << std::endl;
    Domain d = Domain(jr.readJson["domain"], jr.readJson["token"], jr.readJson["follow"]);
    std::cout << d.urlApi << std::endl;
    nlohmann::json f = jr.readJson["follow"];
    for (auto& element: f) {
        std::cout << element["project"] << std::endl;

    }
    return 0;
}

