#include "TravelProfile.h"

bool areEqual(const double d1, const double d2)
{
    if (fabs(d1 - d2) < std::numeric_limits<double>::min())
        return true;
    else 
        return false;
}

TravelProfile::TravelProfile() : ID("-1")
{
    preferredTransportMean = NO_PTM;
    carpoolerPreferredGender = NO_PG;
    specialRequest = NO_SR;
    optimisation = NO_OPT;
    preferredAgeGroup = NO_PAG;
    maxCost = -1.0;
    maxWalkDistance = -1.0;
    maxNumberOfTransfers = -1;
    comfortLevel = -1;
    luggage = false;
    gpsTracking = false;
    food = false;
    pets = false;
    smoking = false;
    music = false;
}

//TravelProfile::TravelProfile(const TravelProfile& tp)
//{
//    this->preferredTransportMean = tp.preferredTransportMean;
//    this->carpoolerPreferredGender = tp.carpoolerPreferredGender;
//    this->specialRequest = tp.specialRequest;
//    this->optimisation = tp.optimisation;
//    this->preferredAgeGroup = tp.preferredAgeGroup;
//    this->maxCost = tp.maxCost;
//    this->maxWalkDistance = tp.maxWalkDistance;
//    this->maxNumberOfTransfers = tp.maxNumberOfTransfers;
//    this->comfortLevel = tp.comfortLevel;
//    this->luggage = tp.luggage;
//    this->gpsTracking = tp.gpsTracking;
//    this->food = tp.food;
//    this->pets = tp.pets;
//    this->smoking = tp.smoking;
//    this->music = tp.music;
//}

TravelProfile::~TravelProfile()
{
}

void TravelProfile::SetID(const std::string ID)
{
    this->ID = ID;
}
 
std::string TravelProfile::GetID() const 
{
    return ID;
}
 
void TravelProfile::SetPreferredTransportMean(const PreferredTransportMean& preferredTransportMean)
{
    this->preferredTransportMean = preferredTransportMean;
}
 
void TravelProfile::SetPreferredTransportMean(const int preferredTransportMean)
{
    if (preferredTransportMean == 0)
        this->preferredTransportMean = NO_PTM;
    else if (preferredTransportMean == 1)
        this->preferredTransportMean = CAR;
    else if (preferredTransportMean == 2)
        this->preferredTransportMean = BUS;
    else if (preferredTransportMean == 3)
        this->preferredTransportMean = WALK;
}
 
PreferredTransportMean TravelProfile::GetPreferredTransportMean() const
{
    return preferredTransportMean;
}
 
std::string TravelProfile::GetPreferredTransportMean_Str() const
{
    if (preferredTransportMean == NO_PTM)
        return "NO_PTM";
    else if (preferredTransportMean == CAR)
        return "CAR";
    else if (preferredTransportMean == BUS)
        return "BUS";
    else if (preferredTransportMean == WALK)
        return "WALK";
}
 
void TravelProfile::SetCarpoolerPreferredGender(const CarpoolerPreferredGender& carpoolerPreferredGender)
{
    this->carpoolerPreferredGender = carpoolerPreferredGender;
}
 
void TravelProfile::SetCarpoolerPreferredGender(const int carpoolerPreferredGender)
{
    if (carpoolerPreferredGender == 0)
        this->carpoolerPreferredGender = NO_PG;
    else if (carpoolerPreferredGender == 1)
        this->carpoolerPreferredGender = MALE;
    else if (carpoolerPreferredGender == 2)
        this->carpoolerPreferredGender = FEMALE;
}
 
CarpoolerPreferredGender TravelProfile::GetCarpoolerPreferredGender() const
{
    return carpoolerPreferredGender;
}
 
std::string TravelProfile::GetCarpoolerPreferredGender_Str() const
{
    if (carpoolerPreferredGender == NO_PG)
        return "NO_PG";
    else if (carpoolerPreferredGender == MALE)
        return "MALE";
    else if (carpoolerPreferredGender == FEMALE)
        return "FEMALE";
}
 
void TravelProfile::SetSpecialRequest(const SpecialRequest specialRequest)
{
    this->specialRequest = specialRequest;
}
 
void TravelProfile::SetSpecialRequest(const int specialRequest)
{
    if (specialRequest == 0)
        this->specialRequest = NO_SR;
    else if (specialRequest == 1)
        this->specialRequest = WHEELCHAIR;
    else if (specialRequest == 2)
        this->specialRequest = BLIND;
    else if (specialRequest == 3)
        this->specialRequest = DEAF;
    else if (specialRequest == 4)
        this->specialRequest = ELDERLY;
}
 
SpecialRequest TravelProfile::GetSpecialRequest() const 
{
    return specialRequest;
}
 
std::string TravelProfile::GetSpecialRequest_Str() const
{
    if (specialRequest == NO_SR)
        return "NO_SR";
    else if (specialRequest == WHEELCHAIR)
        return "WHEELCHAIR";
    else if (specialRequest == BLIND)
        return "BLIND";
    else if (specialRequest == DEAF)
        return "DEAF";
    else if (specialRequest == ELDERLY)
        return "ELDERLY";
}
 
void TravelProfile::SetOptimisation(const Optimisation& optimisation)
{
    this->optimisation = optimisation;
}
 
void TravelProfile::SetOptimisation(const int optimisation)
{
    if (optimisation == 0)
        this->optimisation = NO_OPT;
    else if (optimisation == 1)
        this->optimisation = FASTEST;
    else if (optimisation == 2)
        this->optimisation = SHORTEST;
    else if (optimisation == 3)
        this->optimisation = CHEAPEST;
    else if (optimisation == 4)
        this->optimisation = COMFORT;
    else if (optimisation == 5)
        this->optimisation = SAFEST;
} 
 
Optimisation TravelProfile::GetOptimisation() const 
{
    return optimisation;
}
 
std::string TravelProfile::GetOptimisation_Str() const
{
    if (optimisation == NO_OPT)
        return "NO_OPT";
    else if (optimisation == FASTEST)
        return "FASTEST";
    else if (optimisation == SHORTEST)
        return "SHORTEST";
    else if (optimisation == CHEAPEST)
        return "CHEAPEST";
    else if (optimisation == COMFORT)
        return "COMFORT";
    else if (optimisation == SAFEST)
        return "SAFEST";
}
 
void TravelProfile::SetPreferredAgeGroup(const PreferredAgeGroup& preferredAgeGroup)
{
    this->preferredAgeGroup = preferredAgeGroup;
}
 
void TravelProfile::SetPreferredAgeGroup(const int preferredAgeGroup)
{
    if (preferredAgeGroup == 0)
        this->preferredAgeGroup = NO_PAG;
    else if (preferredAgeGroup == 1)
        this->preferredAgeGroup = AGE_GROUP1;
    else if (preferredAgeGroup == 2)
        this->preferredAgeGroup = AGE_GROUP2;
    else if (preferredAgeGroup == 3)
        this->preferredAgeGroup = AGE_GROUP3;
}
 
PreferredAgeGroup TravelProfile::GetPreferredAgeGroup() const 
{
    return preferredAgeGroup;
}
 
std::string TravelProfile::GetPreferredAgeGroup_Str() const
{
    if (preferredAgeGroup == NO_PAG)
        return "NO_PAG";
    else if (preferredAgeGroup == AGE_GROUP1)
        return "AGE_GROUP1";
    else if (preferredAgeGroup == AGE_GROUP2)
        return "AGE_GROUP2";
    else if (preferredAgeGroup == AGE_GROUP3)
        return "AGE_GROUP3";
}
 
void TravelProfile::SetMaxCost(const double& maxCost)
{
    this->maxCost = maxCost;
}
 
double TravelProfile::getMaxCost() const
{
    return maxCost;
}
 
void TravelProfile::SetMaxWalkDistance(const double& maxWalkDistance)
{
    this->maxWalkDistance = maxWalkDistance;
}
 
double TravelProfile::GetMaxWalkDistance() const
{
    return maxWalkDistance;
}
 
void TravelProfile::SetMaxNumberOfTransfers(const int& maxNumberOfTransfers)
{
    this->maxNumberOfTransfers = maxNumberOfTransfers;
}
 
int TravelProfile::GetMaxNumberOfTransfers() const
{
    return maxNumberOfTransfers;
}
 
void TravelProfile::SetComfortLevel(const int& comfortLevel)
{
    this->comfortLevel = comfortLevel;
}
 
int TravelProfile::GetComfortLevel() const 
{
    return comfortLevel;
}
 
void TravelProfile::SetLuggage(const bool& luggage)
{
    this->luggage = luggage;
}
 
bool TravelProfile::GetLuggage() const
{
    return luggage;
}
 
void TravelProfile::SetGpsTracking(const bool& gpsTracking)
{
    this->gpsTracking = gpsTracking;
}
 
bool TravelProfile::GetGpsTracking() const 
{
    return gpsTracking;
}
 
void TravelProfile::SetFood(const bool& food)
{
    this->food = food;
}
 
bool TravelProfile::GetFood() const
{
    return food;
}
 
void TravelProfile::SetPets(const bool& pets)
{
    this->pets = pets;
}
 
bool TravelProfile::GetPets() const
{
    return pets;
}
 
void TravelProfile::SetSmoking(const bool& smoking)
{
    this->smoking = smoking;
}
 
bool TravelProfile::GetSmoking() const
{
    return smoking;
}
 
void TravelProfile::SetMusic(const bool& music)
{
    this->music = music;
}
 
bool TravelProfile::GetMusic() const
{
    return music;
}
 
TravelProfile TravelProfile::operator=(const TravelProfile& tp)
{
    this->preferredTransportMean = tp.preferredTransportMean;
    this->carpoolerPreferredGender = tp.carpoolerPreferredGender;
    this->specialRequest = tp.specialRequest;
    this->optimisation = tp.optimisation;
    this->preferredAgeGroup = tp.preferredAgeGroup;
    this->maxCost = tp.maxCost;
    this->maxWalkDistance = tp.maxWalkDistance;
    this->maxNumberOfTransfers = tp.maxNumberOfTransfers;
    this->comfortLevel = tp.comfortLevel;
    this->luggage = tp.luggage;
    this->gpsTracking = tp.gpsTracking;
    this->food = tp.food;
    this->pets = tp.pets;
    this->smoking = tp.smoking;
    this->music = tp.music;
    
    return *this;
}

bool TravelProfile::operator==(const TravelProfile& tp)
{
    if 
    (    
        this->preferredTransportMean == tp.preferredTransportMean &&
        this->carpoolerPreferredGender == tp.carpoolerPreferredGender &&
        this->specialRequest == tp.specialRequest &&
        this->optimisation == tp.optimisation &&
        this->preferredAgeGroup == tp.preferredAgeGroup &&
        this->comfortLevel == tp.comfortLevel &&
        this->luggage == tp.luggage &&
        this->gpsTracking == tp.gpsTracking &&
        this->food == tp.food &&
        this->pets == tp.pets &&
        this->smoking == tp.smoking &&
        this->music == tp.music &&
        areEqual(this->maxCost, tp.maxCost) &&
        areEqual(this->maxWalkDistance, tp.maxWalkDistance) &&
        areEqual(this->maxNumberOfTransfers, tp.maxNumberOfTransfers)
    )
        return true;
    else
        return false;
}

void TravelProfile::PrintValuesToConsole()
{
    std::cout << GetPreferredTransportMean_Str() << " " << GetCarpoolerPreferredGender_Str() << " " << GetSpecialRequest_Str() << " "
            << GetOptimisation_Str() << " " << GetPreferredAgeGroup_Str() << " " << comfortLevel << " " << luggage << " "
            << gpsTracking << " " << food << " " << pets << " " << smoking << " " << music << " " << maxCost << " " << maxWalkDistance << " "
            << maxNumberOfTransfers;
}

void TravelProfile::WriteValuesToFile(std::ostream &out)
{
    out << GetPreferredTransportMean_Str() << " " << GetCarpoolerPreferredGender_Str() << " " << GetSpecialRequest_Str() << " "
            << GetOptimisation_Str() << " " << GetPreferredAgeGroup_Str() << " " << comfortLevel << " " << luggage << " "
            << gpsTracking << " " << food << " " << pets << " " << smoking << " " << music << " " << maxCost << " " << maxWalkDistance << " "
            << maxNumberOfTransfers;
}