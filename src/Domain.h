#ifndef REPOTIFY_DOMAIN_H
#define REPOTIFY_DOMAIN_H


#include <string>

class Domain {
public:
    Domain(std::string _url, std::string _token);
    std::string urlApi;

private:
    const std::string url;
    const std::string token;
    const std::string endpointApi;
};


#endif //REPOTIFY_DOMAIN_H
