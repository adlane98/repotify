#include "Project.h"
#include "helpers.h"

#include <utility>
#include <cpr/cpr.h>
#include <sys/stat.h>

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

void Project::makeRequests(const std::string& endpointApi, const std::string& token) {
    for (auto& branchName: branches) {
        std::string request = endpointApi;
        request += "projects/" + std::to_string(id);
        request += "/repository/branches/" + branchName;
        request += "?private_token=" + token;

        auto response = cpr::Get(cpr::Url(request), cpr::VerifySsl(false));
        auto jsonResponse = nlohmann::json::parse(response.text);
        jsonResponses.insert(std::pair<std::string, nlohmann::json>(branchName, jsonResponse));
    }
}

std::string Project::buildFileName(const std::string& domainName, const std::string& branchName) {
    std::string fileName = domainName;
    fileName += "_" + name;
    fileName += "_" + branchName;
    fileName += ".txt";

    return fileName;
}

void Project::writeNewCommitIdFile(const std::string& domainName, const std::string& branchName) {
    std::string fileName = buildFileName(domainName, branchName);
    const std::string folder = "oldcommits/";
    const std::string pathFile = folder + fileName;

    std::ofstream writeFlow(pathFile);
    writeFlow << jsonResponses[branchName]["commit"]["id"].get<std::string>() << std::endl;
    writeFlow.close();
}

void Project::notifyForNewCommit(const std::string& domainName) {
    const std::string folder = "oldcommits/";
    struct stat buf{};
    if (stat(folder.c_str(), &buf) != 0) {
        std::string command = "mkdir -p " + folder;
        system(command.c_str());
    }

    for (auto& jsonResponse: jsonResponses) {
        auto branchName = jsonResponse.first;
        auto commit = jsonResponse.second["commit"];

        std::string fileName = buildFileName(domainName, branchName);
        const std::string pathFile = folder + fileName;

        std::ifstream readFlow(pathFile.c_str());

        if (!readFlow) {
            std::string title = "Suivi de la branche " + branchName + ".";
            std::string description = "Dernier commit : " + commit["title"].get<std::string>();
            showNotification(title, description);
            writeNewCommitIdFile(domainName, branchName);
        }
        else {
            std::string oldId{};
            std::getline(readFlow, oldId);
            
            if (oldId != commit["id"]) {
                std::string title = "Nouveau commit de " + commit["committer_name"].get<std::string>();
                title += " sur la branche " + branchName + ".";
                std::string description = commit["title"].get<std::string>();

                showNotification(title, description);
                writeNewCommitIdFile(domainName, branchName);
            }
        }
    }
}