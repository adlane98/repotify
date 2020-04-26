#ifndef REPOTIFY_JSONREADER_H
#define REPOTIFY_JSONREADER_H


#include <string>
#include <nlohmann/json.hpp>

class JsonReader {
public:
    JsonReader(std::string _pathToJson);
    nlohmann::json readJson;

private:
    std::string pathToJson;
};


#endif //REPOTIFY_JSONREADER_H
