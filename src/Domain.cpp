#include "Domain.h"

#include <utility>

Domain::Domain(std::string _name, std::string _url, std::string _token, nlohmann::json jsonProjects)
: name(std::move(_name)), url(std::move(_url)), token(std::move(_token)), endpointApi("api/v4/")
{
    urlApi = url + endpointApi;
    for (auto& jsonProject: jsonProjects) {
        projects.emplace_back(jsonProject["project"].get<std::string>(), jsonProject["branches"]);
        projects.back().findId(urlApi + "projects?private_token=" + token);
    }
}

void Domain::makeAllRequests() {
    for (auto& project: projects) {
        project.makeRequests(urlApi, token);
        project.notifyForNewCommit(name);
    }
}
