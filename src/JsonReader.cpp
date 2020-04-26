#include <fstream>
#include <utility>
#include "JsonReader.h"

JsonReader::JsonReader(std::string _pathToJson) : pathToJson(std::move(_pathToJson)) {
    std::ifstream readFlow(pathToJson.c_str());
    readFlow >> readJson;
}
