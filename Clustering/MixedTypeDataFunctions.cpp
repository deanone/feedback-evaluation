#include "MixedTypeDataFunctions.h"
#include "Cluster.h"

// Implementation of the Gower's distance metric, for calculating the distance between 2 travel profiles.
double mtdf::CalcDistanceOfPoints(const TravelProfile& tp1, const TravelProfile& tp2)
{
    // distance has values from 0 (inclusive) to 1 (inclusive)
    double distance = 0.0;
    
    // ordinal and continuous
    distance += (std::pow(tp1.getMaxCost() - tp2.getMaxCost(), 2))/std::pow(MAX_COST, 2);
    distance += (std::pow(tp1.GetMaxWalkDistance() - tp2.GetMaxWalkDistance(), 2))/std::pow(MAX_WALK_DISTANCE, 2);
    distance += (std::pow((double)(tp1.GetMaxNumberOfTransfers() - tp2.GetMaxNumberOfTransfers()), 2))/std::pow((double)MAX_NUM_OF_TRANSFERS, 2);
    
    // nominal
    if (tp1.GetPreferredTransportMean() != tp2.GetPreferredTransportMean())
        distance++;
    if (tp1.GetCarpoolerPreferredGender() != tp2.GetCarpoolerPreferredGender())
        distance++;
    if (tp1.GetSpecialRequest() != tp2.GetSpecialRequest())
        distance++;
    if (tp1.GetOptimisation() != tp2.GetOptimisation())
        distance++;
    if (tp1.GetPreferredAgeGroup() != tp2.GetPreferredAgeGroup())
        distance++;
    if (tp1.GetComfortLevel() != tp2.GetComfortLevel())
        distance++;
    
    // binary
    if (tp1.GetLuggage() != tp2.GetLuggage())
        distance++;
    if (tp1.GetGpsTracking() != tp2.GetGpsTracking())
        distance++;
    if (tp1.GetFood() != tp2.GetFood())
        distance++;
    if (tp1.GetPets() != tp2.GetPets())
        distance++;
    if (tp1.GetSmoking() != tp2.GetSmoking())
        distance++;
    if (tp1.GetMusic() != tp2.GetMusic())
        distance++;
    
    distance /= 15.0; // number of variables
            
    return distance;
}

void mtdf::CalculateAverageOfPoints(const Cluster* cl, Cluster* finalCluster)
{
    IntVector preferredTransportMeanVals; preferredTransportMeanVals.assign(4, 0);
    IntVector carpoolerPreferredGenderVals; carpoolerPreferredGenderVals.assign(3, 0);
    IntVector specialRequestVals; specialRequestVals.assign(5, 0);
    IntVector optimisationVals; optimisationVals.assign(6, 0);
    IntVector preferredAgeGroupVals; preferredAgeGroupVals.assign(4, 0);
    IntVector comfortLevelVals; comfortLevelVals.assign(5, 0);
    IntVector luggageVals; luggageVals.assign(2, 0);
    IntVector gpsTrackingVals; gpsTrackingVals.assign(2, 0);
    IntVector foodVals; foodVals.assign(2, 0);
    IntVector petsVals; petsVals.assign(2, 0);
    IntVector smokingVals; smokingVals.assign(2, 0);
    IntVector musicVals; musicVals.assign(2, 0);

    double meanMaxCost = 0.0;
    double meanMaxWalkDistance = 0.0;
    double meanMaxNumberOfTransfers = 0.0;

    int n = cl->pointsOfCluster.size();

    for (int j = 0; j < n; j++)
    {
        // nominal
        PreferredTransportMean ptm = cl->pointsOfCluster[j]->GetPreferredTransportMean();
        if (ptm == NO_PTM)
            preferredTransportMeanVals[NO_PTM]++;
        else if (ptm == CAR)
            preferredTransportMeanVals[CAR]++;
        else if (ptm == BUS)
            preferredTransportMeanVals[BUS]++;
        else if (ptm == WALK)
            preferredTransportMeanVals[WALK]++;

        CarpoolerPreferredGender cpg = cl->pointsOfCluster[j]->GetCarpoolerPreferredGender();

        if (cpg == NO_PG)
            carpoolerPreferredGenderVals[NO_PG]++;
        else if (cpg == MALE)
            carpoolerPreferredGenderVals[MALE]++;
        else if (cpg == FEMALE)
            carpoolerPreferredGenderVals[FEMALE]++;

        SpecialRequest sr = cl->pointsOfCluster[j]->GetSpecialRequest();

        if (sr == NO_SR)
            specialRequestVals[NO_SR]++;
        else if (sr == WHEELCHAIR)
            specialRequestVals[WHEELCHAIR]++;
        else if (sr == BLIND)
            specialRequestVals[BLIND]++;
        else if (sr == DEAF)
            specialRequestVals[DEAF]++;
        else if (sr == ELDERLY)
            specialRequestVals[ELDERLY]++;

        Optimisation opt = cl->pointsOfCluster[j]->GetOptimisation();

        if (opt == NO_OPT)
            optimisationVals[NO_OPT]++;
        else if (opt == FASTEST)
            optimisationVals[FASTEST]++;
        else if (opt == SHORTEST)
            optimisationVals[SHORTEST]++;
        else if (opt == CHEAPEST)
            optimisationVals[CHEAPEST]++;
        else if (opt == COMFORT)
            optimisationVals[COMFORT]++;
        else if (opt == SAFEST)
            optimisationVals[SAFEST]++;

        PreferredAgeGroup pag = cl->pointsOfCluster[j]->GetPreferredAgeGroup();

        if (pag == NO_PAG)
            preferredAgeGroupVals[NO_PAG]++;
        else if (pag == AGE_GROUP1)
            preferredAgeGroupVals[AGE_GROUP1]++;
        else if (pag == AGE_GROUP2)
            preferredAgeGroupVals[AGE_GROUP2]++;
        else if (pag == AGE_GROUP3)
            preferredAgeGroupVals[AGE_GROUP3]++;

        int comfortLevel = cl->pointsOfCluster[j]->GetComfortLevel();

        if (comfortLevel == 1)
            comfortLevelVals[0]++;
        else if (comfortLevel == 2)
            comfortLevelVals[1]++;
        else if (comfortLevel == 3)
            comfortLevelVals[2]++;
        else if (comfortLevel == 4)
            comfortLevelVals[3]++;
        else if (comfortLevel == 5)
            comfortLevelVals[4]++;

        bool lug = cl->pointsOfCluster[j]->GetLuggage();

        // binary
        if (!lug)
            luggageVals[0]++;
        else
            luggageVals[1]++;

        bool gpsTrack = cl->pointsOfCluster[j]->GetGpsTracking();

        if (!gpsTrack)
            gpsTrackingVals[0]++;
        else
            gpsTrackingVals[1]++;

        bool food = cl->pointsOfCluster[j]->GetFood();

        if (!food)
            foodVals[0]++;
        else
            foodVals[1]++;

        bool pets = cl->pointsOfCluster[j]->GetPets();

        if (!pets)
            petsVals[0]++;
        else
            petsVals[1]++;

        bool smoking = cl->pointsOfCluster[j]->GetSmoking();

        if (!smoking)
            smokingVals[0]++;
        else
            smokingVals[1]++;

        bool music = cl->pointsOfCluster[j]->GetMusic();

        if (!music)
            musicVals[0]++;
        else
            musicVals[1]++;

        // ordinal and continuous
        meanMaxCost += cl->pointsOfCluster[j]->getMaxCost();
        meanMaxWalkDistance += cl->pointsOfCluster[j]->GetMaxWalkDistance();
        meanMaxNumberOfTransfers += (double)(cl->pointsOfCluster[j]->GetMaxNumberOfTransfers());
    }

    int preferredTransportMeanVal = std::max_element(preferredTransportMeanVals.begin(), preferredTransportMeanVals.end()) - preferredTransportMeanVals.begin();
    preferredTransportMeanVals.clear();
    int carpoolerPreferredGenderVal = std::max_element(carpoolerPreferredGenderVals.begin(), carpoolerPreferredGenderVals.end()) - carpoolerPreferredGenderVals.begin();
    carpoolerPreferredGenderVals.clear();
    int specialRequestVal = std::max_element(specialRequestVals.begin(), specialRequestVals.end()) - specialRequestVals.begin();
    specialRequestVals.clear();
    int optimisationVal = std::max_element(optimisationVals.begin(), optimisationVals.end()) - optimisationVals.begin();
    optimisationVals.clear();
    int preferredAgeGroupVal = std::max_element(preferredAgeGroupVals.begin(), preferredAgeGroupVals.end()) - preferredAgeGroupVals.begin();
    preferredAgeGroupVals.clear();
    int comfortLevelVal = std::max_element(comfortLevelVals.begin(), comfortLevelVals.end()) - comfortLevelVals.begin();
    comfortLevelVals.clear();
    int luggageVal = std::max_element(luggageVals.begin(), luggageVals.end()) - luggageVals.begin();
    luggageVals.clear();
    int gpsTrackingVal = std::max_element(gpsTrackingVals.begin(), gpsTrackingVals.end()) - gpsTrackingVals.begin();
    gpsTrackingVals.clear();
    int foodVal = std::max_element(foodVals.begin(), foodVals.end()) - foodVals.begin();
    foodVals.clear();
    int petsVal = std::max_element(petsVals.begin(), petsVals.end()) - petsVals.begin();
    petsVals.clear();
    int smokingVal = std::max_element(smokingVals.begin(), smokingVals.end()) - smokingVals.begin();
    smokingVals.clear();
    int musicVal = std::max_element(musicVals.begin(), musicVals.end()) - musicVals.begin();
    musicVals.clear();
    meanMaxCost /= (double)n;
    meanMaxWalkDistance /= (double)n;
    meanMaxNumberOfTransfers /= (double)n;

    TravelProfile tp;

    tp.SetPreferredTransportMean(preferredTransportMeanVal);
    tp.SetCarpoolerPreferredGender(carpoolerPreferredGenderVal);
    tp.SetSpecialRequest(specialRequestVal);
    tp.SetOptimisation(optimisationVal);
    tp.SetPreferredAgeGroup(preferredAgeGroupVal);
    tp.SetComfortLevel(comfortLevelVal);

    tp.SetLuggage(!(luggageVal == 0));
    tp.SetGpsTracking(!(gpsTrackingVal == 0));
    tp.SetFood(!(foodVal == 0));
    tp.SetPets(!(petsVal == 0));
    tp.SetSmoking(!(smokingVal == 0));
    tp.SetMusic(!(musicVal == 0));

    tp.SetMaxNumberOfTransfers(meanMaxNumberOfTransfers);
    tp.SetMaxCost(meanMaxCost);
    tp.SetMaxWalkDistance(meanMaxWalkDistance);

    finalCluster->center = tp;
}