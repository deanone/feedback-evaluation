/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reputation.h
 * Author: asal
 *
 * Created on February 24, 2017, 10:41 AM
 */

#ifndef REPUTATION_H
#define REPUTATION_H

#include "DataTypes.h"

class Reputation
{
    int r;
    int s;
    int rep;
    int lastUpdate;
    std::string _id;
    
public:
    
    Reputation(int R, int S, int REP, int LastUpdate, std::string _ID);
    ~Reputation();
    
    void SetR(const int r) { this->r = r;}
    int GetR() const {return r;}
    
    void SetS(const int s) { this->s = s;}
    int GetS() const {return s;}
    
    void SetRep(const int rep) {this->rep = rep;}
    int GetRep() const {return rep;}
    
    void SetLastUpdate(const int lastUpdate) {this->lastUpdate = lastUpdate;}
    int GetLastUpdate() const {return lastUpdate;}
    
    void Set_id(const std::string _id) {this->_id = _id;}
    std::string Get_id() const {return _id;}
    
};

#endif /* REPUTATION_H */

