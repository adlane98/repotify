#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <iostream>
#include <gdk-pixbuf/gdk-pixbuf-core.h>
#include <libnotify/notify.h>


nlohmann::json make_request(const std::string &private_token) {
    std::string url("https://gitlab.caciis.net/api/v4/projects/168/repository/branches?private_token=");
    auto response = cpr::Get(cpr::Url{url + private_token},cpr::VerifySsl(false));
    nlohmann::json json_parsing = nlohmann::json::parse(response.text);

    return json_parsing;
}

void showNotification(const std::string& title, const std::string& description) {
    std::cout << "Notification !" << std::endl;
    notify_init("Repotify");
    NotifyNotification* n = notify_notification_new(title.c_str(), description.c_str(), nullptr);
    notify_notification_set_timeout(n, 10000);
    notify_notification_show(n, nullptr);
    notify_uninit();

    std::this_thread::sleep_for(std::chrono::milliseconds(7500));
}

void write_new_commit(const nlohmann::json& json_to_write, const char* path_file) {
    std::ofstream write_flow(path_file);
    write_flow << json_to_write.dump() << std::endl;
    write_flow.close();
    std::cout << "Ecriture du nouveau fichier de commit." << std::endl;
}
