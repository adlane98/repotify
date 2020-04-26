#ifndef REPOTIFY_PROJECT_H
#define REPOTIFY_PROJECT_H


#include <string>
#include <vector>
#include <nlohmann/json.hpp>


class Project {
public:
    Project(std::string _name, const nlohmann::json& jsonBranches);

    void findId(std::string url);

private:
    const std::string name;
    int id;
    std::vector<std::string> branches;
};


#endif //REPOTIFY_PROJECT_H
