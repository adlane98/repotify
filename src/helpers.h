#ifndef REPOTIFY_HELPERS_H
#define REPOTIFY_HELPERS_H

#include <nlohmann/json.hpp>

nlohmann::json makeRequest(const std::string& privateToken);
void showNotification(const std::string& title, const std::string& description);
void write_new_commit(const nlohmann::json& json_to_write, const char* path_file);


#endif //REPOTIFY_HELPERS_H
