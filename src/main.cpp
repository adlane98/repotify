#include <iostream>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"
#include <sys/stat.h>
#include <libnotify/notify.h>

void show_notification(const char*, const char*);
void write_new_commit(const nlohmann::json&, const char*);

int main() {
    std::cout << "Lancement du programme." << std::endl;

    // Recuperation de la clef privee
    std::ifstream token_flow{R"(token.txt)"};
    std::string private_token{};
    std::getline(token_flow, private_token);
    token_flow.close();

    struct stat buffer{};

    // Si inexistant creation du dossier olcommits
    std::string filename = "commits.json";
    std::string path = "oldcommits/repo-test/";
    std::string path_filename = path + filename;
    std::cout << path_filename << std::endl;

    if (stat(path.c_str(), &buffer) != 0) {
        std::string command = "mkdir -p " + path;
        system(command.c_str());
    }

    std::ifstream read_flow(path_filename.c_str());
    // Si le fichier des derniers commits d'un projet n'existe pas on le cree
    if (!read_flow) {
        auto response = cpr::Get(cpr::Url{
                                         "https://gitlab.caciis.net/api/v4/projects/168/repository/branches?private_token=" + private_token},
                                 cpr::VerifySsl(
                                         false));
        nlohmann::json json = nlohmann::json::parse(response.text);
        show_notification("Nouveau repo", "C'est parti !");
        write_new_commit(json, path_filename.c_str());
        // Sinon on le lit
    } else {
        std::string json_line{};
        std::getline(read_flow, json_line);
        auto old_json = nlohmann::json::parse(json_line);

        auto response = cpr::Get(cpr::Url{
                                         "https://gitlab.caciis.net/api/v4/projects/168/repository/branches?private_token=" + private_token},
                                 cpr::VerifySsl(
                                         false));
        nlohmann::json new_json = nlohmann::json::parse(response.text);

        for (auto &old_branch_item: old_json.items()) {
            for (auto &new_branch_item: new_json.items()) {
                auto old_branch = old_branch_item.value();
                auto new_branch = new_branch_item.value();
                if (old_branch["name"] == new_branch["name"] && old_branch["name"] == "master") {
                    if (old_branch["commit"]["id"] != new_branch["commit"]["id"]) {
                        std::cout << "Nouveau commit !" << std::endl;
                        show_notification("Nouveau commit", "Salut !");
                        write_new_commit(new_json, path_filename.c_str());
                    }
                }
            }
        }

    }
    return 0;
}

void write_new_commit(const nlohmann::json& json_to_write, const char* path_file) {
    std::ofstream write_flow(path_file);
    write_flow << json_to_write.dump() << std::endl;
    write_flow.close();
    std::cout << "Ecriture du nouveau fichier de commit." << std::endl;
}

void show_notification(const char* title, const char* description) {
    std::cout << "Notification !" << std::endl;
    notify_init("Test repotify");
    NotifyNotification* n = notify_notification_new(title, description, "dialog-information");
    notify_notification_set_timeout(n, 10000);
    notify_notification_show(n, 0);
    notify_uninit();
}
