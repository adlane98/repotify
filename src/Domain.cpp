#include "Domain.h"

#include <utility>

Domain::Domain(std::string _url, std::string _token)
: url(std::move(_url)), token(std::move(_token)), endpointApi("api/v4/")
{
    urlApi = url + endpointApi;
}
