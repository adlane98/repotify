#include "Project.h"

#include <utility>
#include <cpr/cpr.h>

Project::Project(std::string _name, const nlohmann::json& jsonBranches)
: name(std::move(_name)), id(-1)
{
    for (auto& element: jsonBranches) {
        branches.push_back(element.get<std::string>());
    }
}

void Project::findId(std::string url) {
    auto response = cpr::Get(cpr::Url{std::move(url)}, cpr::VerifySsl(false));
    auto jsonResponse = nlohmann::json::parse(response.text);

    for (auto& jsonProject: jsonResponse) {
        if (jsonProject["name"] == name) {
            id = jsonProject["id"];
            break;
        }
    }
}
