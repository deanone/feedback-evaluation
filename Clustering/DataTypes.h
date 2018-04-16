/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataTypes.h
 * Author: asal
 *
 * Created on January 20, 2017, 11:11 AM
 */

#ifndef DATATYPES_H
#define DATATYPES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>
#include <complex>
#include <vector>
#include <map>
#include <utility>
#include <limits>
#include <ctime>
#include <linux/limits.h>
#include <unistd.h>

enum PreferredTransportMean{NO_PTM, CAR, BUS, WALK};
enum CarpoolerPreferredGender{NO_PG, MALE, FEMALE};
enum SpecialRequest{NO_SR, WHEELCHAIR,  BLIND, DEAF, ELDERLY};
enum Optimisation{NO_OPT, FASTEST, SHORTEST, CHEAPEST, COMFORT, SAFEST};
enum PreferredAgeGroup{NO_PAG, AGE_GROUP1, AGE_GROUP2, AGE_GROUP3};  // AGE_GROUP = X, X >= 1 MEANS AGE_GROUP = [(X+1)*10, (X+1)*10 + 10] WITH X IN YEARS

// for normalizing ordinal and continuous variables by range

const double MAX_COST = 20.0;
const double MAX_WALK_DISTANCE = 1000.0;
const int MAX_NUM_OF_TRANSFERS = 10;

typedef std::vector<int> IntVector;
typedef std::vector<std::string> StringVector;
typedef std::vector<float> FloatVector;
typedef std::vector<double> DoubleVector;
typedef std::pair<int,int> IntIntPair;
typedef std::pair<int,float> IntFloatPair;
typedef std::map<int,FloatVector> IntFloatVectorMap;

#endif /* DATATYPES_H */

