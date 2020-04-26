#include <iostream>
#include "nlohmann/json.hpp"
#include "JsonReader.h"
#include "Domain.h"
#include <iomanip>



int main() {
    JsonReader jr = JsonReader("../app_config.json");
    std::cout << std::setw(4) << jr.readJson << std::endl;
    Domain d = Domain(jr.readJson["name"], jr.readJson["domain"], jr.readJson["token"], jr.readJson["follow"]);
    std::cout << d.urlApi << std::endl;
    nlohmann::json f = jr.readJson["follow"];
    for (auto& element: f) {
        std::cout << element["project"] << std::endl;

    }
    d.makeAllRequests();
    return 0;
}

