#include <string>
#include <typeinfo>

#include "WebService.h"
#include "restclient.h"
#include "DataTypes.h"

WebService::WebService(void)
{
}

WebService::~WebService(void)
{
}

std::string WebService::GetTravelPreferences(std::string BASE_URL)
{    
    std::string url = BASE_URL + "users";
    RestClient::setAuth("admin", "password");
    //std::cout << url << std::endl;
    RestClient::response r = RestClient::get(url);
    return r.body;
}