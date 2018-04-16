/* 
 * File:   WebService.h
 * Author: asal
 *
 * Created on February 23, 2017, 11:28 AM
 */

#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <string>

class WebService
{
public:
    WebService(void);
    ~WebService(void);
    std::string GetRatings(std::string BASE_URL, long int timestamp);
    std::string GetReputations(std::string BASE_URL);
    std::string GetReputation(std::string BASE_URL, std::string user_id);
    std::string PutReputation(std::string BASE_URL, std::string _id, std::string newUserReputationRecord);
    std::string GetUsers(std::string BASE_URL);
    std::string GetUser(std::string BASE_URL, std::string user_id);
    std::string PutUser(std::string BASE_URL, std::string user_id, std::string newUserReputationRecord);
};

#endif /* WEBSERVICE_H */

