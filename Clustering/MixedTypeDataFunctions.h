/* 
 * File:   MixedTypeDataFunctions.h
 * Author: asal
 *
 * Created on January 20, 2017, 3:09 PM
 */

#ifndef MIXEDTYPEDATAFUNCTIONS_H
#define MIXEDTYPEDATAFUNCTIONS_H

#include "TravelProfile.h"
#include "Cluster.h"

namespace mtdf
{
    double CalcDistanceOfPoints(const TravelProfile& tp1, const TravelProfile& tp2);
    void CalculateAverageOfPoints(const Cluster* cl, Cluster* finalCluster);
}

#endif /* MIXEDTYPEDATAFUNCTIONS_H */

