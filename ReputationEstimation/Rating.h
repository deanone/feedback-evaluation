/* 
 * File:   Rating.h
 * Author: asal
 *
 * Created on February 16, 2017, 1:04 PM
 */

#ifndef RATING_H
#define RATING_H

#include "DataTypes.h"

class Rating
{
    std::string reviewerID;
    std::string reviewedID;
    IntVector ratingVals;
    double meanRating;

public:
    Rating(std::string reviewer, std::string reviewed);
    ~Rating();

    void SetReviewerID(const std::string reviewerID) {this->reviewerID = reviewerID;}
    std::string GetReviewerID() const {return reviewerID;}
    
    void SetReviewedID(const std::string reviewedID) {this->reviewedID = reviewedID;}
    std::string GetReviewedID() const {return reviewedID;}
    
    void CalculateMeanRating();
    double GetMeanRating() const { return meanRating;}
    void AddRatingVal(const int ratingVal) {ratingVals.push_back(ratingVal);}
};

#endif /* RATING_H */

