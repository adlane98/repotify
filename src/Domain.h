#ifndef REPOTIFY_DOMAIN_H
#define REPOTIFY_DOMAIN_H


#include <string>
#include <nlohmann/json.hpp>
#include "Project.h"

class Domain {
public:
    Domain(std::string _url, std::string _token, nlohmann::json jsonProjects);
    std::string urlApi;

private:
    const std::string url;
    const std::string token;
    const std::string endpointApi;
    std::vector<Project> projects;
};


#endif //REPOTIFY_DOMAIN_H
