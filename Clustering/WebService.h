/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WebService.h
 * Author: asal
 *
 * Created on February 23, 2017, 2:35 PM
 */

#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <string>

class WebService
{
public:
    WebService(void);
    ~WebService(void);
    std::string GetTravelPreferences(std::string BASE_URL);
};

#endif /* WEBSERVICE_H */

