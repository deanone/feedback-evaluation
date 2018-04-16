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

std::string WebService::GetRatings(std::string BASE_URL, long int timestamp)
{    
    std::string url = BASE_URL + "feedbacks?date_$gt=";
    url += std::to_string(timestamp);
    //std::string url = BASE_URL + "feedbacks";
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::get(url);
    return r.body;
}

std::string WebService::GetReputations(std::string BASE_URL)
{    
    std::string url = BASE_URL + "reputations";
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::get(url);
    return r.body;
}

std::string WebService::GetReputation(std::string BASE_URL, std::string user_id)
{
    std::string url = BASE_URL +"reputations/";
    url += user_id;
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::get(url);
    return r.body;
}

std::string WebService::PutReputation(std::string BASE_URL, std::string _id, std::string newUserReputationRecord)
{
    std::string url =  BASE_URL + "reputations/";
    url += _id;
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::put(url, "application/json", newUserReputationRecord);
    return r.body;
}

std::string WebService::GetUsers(std::string BASE_URL)
{
    std::string url = BASE_URL + "users";
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::get(url);
    return r.body;
}

std::string WebService::GetUser(std::string BASE_URL, std::string user_id)
{
    std::string url = BASE_URL +"users/";
    url += user_id;
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::get(url);
    return r.body;
}

std::string WebService::PutUser(std::string BASE_URL, std::string _id, std::string newUserReputationRecord)
{
    std::string url =  BASE_URL + "users/";
    url += _id;
    RestClient::setAuth("admin", "password");
    RestClient::response r = RestClient::put(url, "application/json", newUserReputationRecord);
    return r.body;
}