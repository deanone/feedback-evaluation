#include "Rating.h"

Rating::Rating(std::string reviewer, std::string reviewed) : reviewerID(reviewer), reviewedID(reviewed)
{
    meanRating = 0.0;
}

Rating::~Rating()
{
    if (ratingVals.size() > 0)
        ratingVals.clear();
}

void Rating::CalculateMeanRating()
{
    bool allValidValues = true;
    for (auto ratingVal : ratingVals)
    {
        if ((ratingVal < 1) || (ratingVal > 5))
        {
            allValidValues = false;
            break;
        }
    }
    if (allValidValues)
    {
        meanRating = std::accumulate(ratingVals.begin(), ratingVals.end(), 0.0);
        meanRating /= ratingVals.size();
    }
}