/* 
 * File:   TravelProfile.h
 * Author: asal
 *
 * Created on January 20, 2017, 11:07 AM
 */

#ifndef TRAVELPROFILE_H
#define TRAVELPROFILE_H

#include "DataTypes.h"

class TravelProfile
{
    std::string ID;
    
    // nominal variables
    PreferredTransportMean preferredTransportMean;
    CarpoolerPreferredGender carpoolerPreferredGender;
    SpecialRequest specialRequest;
    Optimisation optimisation;
    PreferredAgeGroup preferredAgeGroup;
    int comfortLevel; // e.g. from 1 to 5
    
    // binary variables
    bool luggage;
    bool gpsTracking;
    bool food;
    bool pets;
    bool smoking;
    bool music;
    
    // ordinal and continuous variables
    double maxCost;
    double maxWalkDistance;
    int maxNumberOfTransfers;
            
public:
    TravelProfile();
    //TravelProfile(const TravelProfile& tp);
    ~TravelProfile();
    
    // setters, getters
    void SetID(const std::string ID);
    std::string GetID() const;
    
    void SetPreferredTransportMean(const PreferredTransportMean& preferredTransportMean);
    void SetPreferredTransportMean(const int preferredTransportMean);
    PreferredTransportMean GetPreferredTransportMean() const;
    std::string GetPreferredTransportMean_Str() const; 
    
    void SetCarpoolerPreferredGender(const CarpoolerPreferredGender& carpoolerPreferredGender);
    void SetCarpoolerPreferredGender(const int carpoolerPreferredGender);
    CarpoolerPreferredGender GetCarpoolerPreferredGender() const;
    std::string GetCarpoolerPreferredGender_Str() const;
    
    void SetSpecialRequest(const SpecialRequest specialRequest);
    void SetSpecialRequest(const int specialRequest);
    SpecialRequest GetSpecialRequest() const;
    std::string GetSpecialRequest_Str() const;
    
    void SetOptimisation(const Optimisation& optimisation);
    void SetOptimisation(const int optimisation);
    Optimisation GetOptimisation() const;
    std::string GetOptimisation_Str() const;
    
    void SetPreferredAgeGroup(const PreferredAgeGroup& preferredAgeGroup);
    void SetPreferredAgeGroup(const int preferredAgeGroup);
    PreferredAgeGroup GetPreferredAgeGroup() const;
    std::string GetPreferredAgeGroup_Str() const;
    
    void SetMaxCost(const double& maxCost);
    double getMaxCost() const;
    
    void SetMaxWalkDistance(const double& maxWalkDistance);
    double GetMaxWalkDistance() const;
    
    void SetMaxNumberOfTransfers(const int& maxNumberOfTransfers);
    int GetMaxNumberOfTransfers() const;
    
    void SetComfortLevel(const int& comfortLevel);
    int GetComfortLevel() const;
    
    void SetLuggage(const bool& luggage);
    bool GetLuggage() const;
    
    void SetGpsTracking(const bool& gpsTracking);
    bool GetGpsTracking() const;
    
    void SetFood(const bool& food);
    bool GetFood() const;
    
    void SetPets(const bool& pets);
    bool GetPets() const;
    
    void SetSmoking(const bool& smoking);
    bool GetSmoking() const;
    
    void SetMusic(const bool& music);
    bool GetMusic() const;
    
    TravelProfile operator=(const TravelProfile& tp);
    bool operator==(const TravelProfile& tp);
    
    void PrintValuesToConsole();
    void WriteValuesToFile(std::ostream &out);
    
};

#endif /* TRAVELPROFILE_H */

