#ifndef REPOTIFY_PROJECT_H
#define REPOTIFY_PROJECT_H


#include <string>
#include <vector>
#include <nlohmann/json.hpp>


class Project {
public:
    Project(std::string _name, const nlohmann::json& jsonBranches);

    void findId(std::string url);
    void makeRequests(const std::string& endpointApi, const std::string& token);
    void writeNewCommitIdFile(const std::string& domainName, const std::string& branchName);
    void notifyForNewCommit(const std::string& domainName);
private:
    const std::string name;
    int id;
    std::vector<std::string> branches;
    std::map<std::string, nlohmann::json> jsonResponses;

    std::string buildFileName(const std::string &domainName, const std::string &branchName);
};


#endif //REPOTIFY_PROJECT_H
