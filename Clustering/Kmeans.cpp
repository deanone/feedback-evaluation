#include "Kmeans.h"
#include "PropertiesParser.h"
#include "MixedTypeDataFunctions.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "WebService.h"

using namespace rapidjson;

Kmeans::Kmeans(std::string datasetFilename, int numOfClusters, int numOfIt) : k(numOfClusters), numOfIterations(numOfIt)
{
    std::string dataline;
    std::ifstream in;
    in.open(datasetFilename.c_str(), std::ios::in);
    if (in.is_open())
    {
        int i = 0;
        while(std::getline(in, dataline))
        { 
            std::stringstream ss(dataline);
            std::string item;
            StringVector items;
            while (getline(ss, item, ' '))
                items.push_back(item);
            
            TravelProfile tp;
            
            std::string ID = items[0];
            tp.SetID(ID);
            
            PreferredTransportMean preferredTransportMean;
            if (items[1].compare("CAR") == 0)
                preferredTransportMean = CAR;
            else if (items[1].compare("BUS") == 0)
                preferredTransportMean = BUS;
            else if (items[1].compare("WALK") == 0)
                preferredTransportMean = WALK;
            else
                preferredTransportMean = NO_PTM;
            
            tp.SetPreferredTransportMean(preferredTransportMean);
            
            CarpoolerPreferredGender carpoolerPreferredGender;
            if (items[2].compare("MALE") == 0)
                carpoolerPreferredGender = MALE;
            else if (items[2].compare("FEMALE") == 0)
                carpoolerPreferredGender = FEMALE;
            else
                carpoolerPreferredGender = NO_PG;
            
            tp.SetCarpoolerPreferredGender(carpoolerPreferredGender);
            
            SpecialRequest specialRequest;
            if (items[3].compare("WHEELCHAIR") == 0)
                specialRequest = WHEELCHAIR;
            else if (items[3].compare("BLIND") == 0)
                specialRequest = BLIND;
            else if (items[3].compare("DEAF") == 0)
                specialRequest = DEAF;
            else if (items[3].compare("ELDERLY") == 0)
                specialRequest = ELDERLY;
            else
                specialRequest = NO_SR;
                   
            tp.SetSpecialRequest(specialRequest);
            
            Optimisation optimisation;
            if (items[4].compare("FASTEST") == 0)
                optimisation = FASTEST;
            else if (items[4].compare("SHORTEST") == 0)
                optimisation = SHORTEST;
            else if (items[4].compare("CHEAPEST") == 0)
                optimisation = CHEAPEST;
            else if (items[4].compare("COMFORT") == 0)
                optimisation = COMFORT;
            else if (items[4].compare("SAFEST") == 0)
                optimisation = SAFEST;
            else
                optimisation = NO_OPT;
            
            tp.SetOptimisation(optimisation);

            int preferredAgeGroup_i = std::stoi(items[5]);
            if (preferredAgeGroup_i == 0)
                tp.SetPreferredAgeGroup(0);
            else if (preferredAgeGroup_i == 1)
                tp.SetPreferredAgeGroup(1);
            else if (preferredAgeGroup_i == 2)
                tp.SetPreferredAgeGroup(2);
            else
                tp.SetPreferredAgeGroup(3);
            
            tp.SetComfortLevel(std::stoi(items[6]));
            tp.SetLuggage(!(std::stoi(items[7]) == 0));
            tp.SetGpsTracking(!(std::stoi(items[8]) == 0));
            tp.SetFood(!(std::stoi(items[9]) == 0));
            tp.SetPets(!(std::stoi(items[10]) == 0));
            tp.SetSmoking(!(std::stoi(items[11]) == 0));
            tp.SetMusic(!(std::stoi(items[12]) == 0));
            
            tp.SetMaxCost(std::stof(items[13]));
            tp.SetMaxWalkDistance(std::stof(items[14]));
            tp.SetMaxNumberOfTransfers(std::stoi(items[15]));
            
            items.clear();
            points.push_back(tp);
            i++;
        }
        in.close();
    }
    else
        std::cout << "Cannot open file.\n";
    
    // Create initial and final clusters
    for (int i = 0 ; i < k ; i++)
    {
        Cluster* initial = new Cluster(i);
        initialClusters.push_back(initial);
        Cluster* final = new Cluster(i);
        finalClusters.push_back(final);
    }
}

Kmeans::Kmeans(int numOfClusters, int numOfIt, std::string BASE_URL) : k(numOfClusters), numOfIterations(numOfIt)
{
    WebService* srv = new WebService();
    std::string response = "";
    response = srv->GetTravelPreferences(BASE_URL);
    //std::cout << response << std::endl;
    delete srv;
    noData = true;
    bool firstTime = true;
    size_t numOfValidUsers = 0; // a user is considered "valid" if he/she has values for all the travel preferences fields
    // take travel preferences from MongoDB and save them in the TravelPreferences.txt file in the appropriate format
    if (response.compare("Failed to query.") != 0)
    {
        Document d;
        d.Parse(response.c_str());
        if (d.IsObject() && d.HasMember("users"))
        {
            Value& users_json = d["users"];
            if ((users_json.IsArray()) && (users_json.Size() > 0))
            {
                for (SizeType i = 0; i < users_json.Size(); i++)
                {
                    if ((users_json[i].IsObject()) && (users_json[i].HasMember("_id")) && (users_json[i].HasMember("travel_preferences")))
                    {
                        TravelProfile tp;

                        // user_id
                        std::string user_id_s = "";
                        Value& user_id_json = users_json[i]["_id"];
                        if (user_id_json.IsString()) user_id_s = user_id_json.GetString();
                        else continue;
                        tp.SetID(user_id_s);

                        // travel preferences features
                        Value& travel_preferences_json = users_json[i]["travel_preferences"];
                        if (travel_preferences_json.IsObject() && (travel_preferences_json.HasMember("preferred_transport") || travel_preferences_json.HasMember("carpooler_preferred_gender")
                            || travel_preferences_json.HasMember("special_request") || travel_preferences_json.HasMember("optimisation") || travel_preferences_json.HasMember("carpooler_preferred_age_group")
                            || travel_preferences_json.HasMember("comfort_level") || travel_preferences_json.HasMember("luggage") || travel_preferences_json.HasMember("gps_tracking")
                            || travel_preferences_json.HasMember("food") || travel_preferences_json.HasMember("pets") || travel_preferences_json.HasMember("smoking")  
                            || travel_preferences_json.HasMember("music") || travel_preferences_json.HasMember("max_cost") || travel_preferences_json.HasMember("max_walk_distance")
                            || travel_preferences_json.HasMember("max_transfers")) )
                        {
                            numOfValidUsers++;

                            // preferred transport mean
                            PreferredTransportMean preferredTransportMean = NO_PTM;
                            if (travel_preferences_json.HasMember("preferred_transport"))
                            {
                                std::string preferredTransportMean_s = "";
                                Value& preferredTransportMean_json = travel_preferences_json["preferred_transport"];
                                if ((preferredTransportMean_json.IsArray()) && (preferredTransportMean_json.Size() > 0) && (preferredTransportMean_json[0].IsString()))
                                {
                                    preferredTransportMean_s = preferredTransportMean_json[0].GetString();         
                                    if (preferredTransportMean_s.compare("CAR") == 0)
                                        preferredTransportMean = CAR;
                                    else if (preferredTransportMean_s.compare("BUS") == 0)
                                        preferredTransportMean = BUS;
                                    else if (preferredTransportMean_s.compare("WALK") == 0)
                                        preferredTransportMean = WALK;
                                    else
                                        preferredTransportMean = NO_PTM;
                                }
                            }                          
                            tp.SetPreferredTransportMean(preferredTransportMean);

                            // preferred carpooler gender
                            CarpoolerPreferredGender carpoolerPreferredGender = NO_PG;
                            if (travel_preferences_json.HasMember("carpooler_preferred_gender"))
                            {
                                std::string carpoolerPreferredGender_s = "";                       
                                Value& carpoolerPreferredGender_json = travel_preferences_json["carpooler_preferred_gender"];
                                if (carpoolerPreferredGender_json.IsString())
                                {
                                    carpoolerPreferredGender_s = carpoolerPreferredGender_json.GetString();
                                    if (carpoolerPreferredGender_s.compare("MALE") == 0)
                                        carpoolerPreferredGender = MALE;
                                    else if (carpoolerPreferredGender_s.compare("FEMALE") == 0)
                                        carpoolerPreferredGender = FEMALE;
                                    else
                                        carpoolerPreferredGender = NO_PG;
                                }
                            }
                            tp.SetCarpoolerPreferredGender(carpoolerPreferredGender);

                            // special request
                            SpecialRequest specialRequest = NO_SR;
                            if (travel_preferences_json.HasMember("special_request"))
                            {
                                std::string specialRequest_s = "";
                                Value& specialRequest_json = travel_preferences_json["special_request"];
                                if ((specialRequest_json.IsArray()) && (specialRequest_json.Size() > 0) && (specialRequest_json[0].IsString()))
                                {
                                    specialRequest_s = specialRequest_json[0].GetString();
                                    if (specialRequest_s.compare("WHEELCHAIR") == 0)
                                        specialRequest = WHEELCHAIR;
                                    else if (specialRequest_s.compare("BLIND") == 0)
                                        specialRequest = BLIND;
                                    else if (specialRequest_s.compare("DEAF") == 0)
                                        specialRequest = DEAF;
                                    else if (specialRequest_s.compare("ELDERLY") == 0)
                                        specialRequest = ELDERLY;
                                    else
                                        specialRequest = NO_SR;
                                }
                            }
                            tp.SetSpecialRequest(specialRequest);

                            // optimization
                            Optimisation optimisation = NO_OPT;
                            if (travel_preferences_json.HasMember("optimisation"))
                            {
                                std::string optimisation_s = "";
                                Value& optimisation_json = travel_preferences_json["optimisation"];
                                if ((optimisation_json.IsArray()) && (optimisation_json.Size() > 0) && (optimisation_json[0].IsString()))
                                {
                                    optimisation_s = optimisation_json[0].GetString();
                                    if (optimisation_s.compare("FASTEST") == 0)
                                        optimisation = FASTEST;
                                    else if (optimisation_s.compare("SHORTEST") == 0)
                                        optimisation = SHORTEST;
                                    else if (optimisation_s.compare("CHEAPEST") == 0)
                                        optimisation = CHEAPEST;
                                    else if (optimisation_s.compare("COMFORT") == 0)
                                        optimisation = COMFORT;
                                    else if (optimisation_s.compare("SAFEST") == 0)
                                        optimisation = SAFEST;
                                    else
                                        optimisation = NO_OPT;
                                }   
                            }
                            tp.SetOptimisation(optimisation);

                            // preferred carpooler age group (20-30, 30-40, 40-50)
                            if (travel_preferences_json.HasMember("carpooler_preferred_age_group"))
                            {
                                std::string preferredAgeGroup_s = "";
                                Value& preferredAgeGroup_json = travel_preferences_json["carpooler_preferred_age_group"];
                                if (preferredAgeGroup_json.IsString())
                                {
                                    preferredAgeGroup_s = preferredAgeGroup_json.GetString();
                                    if (preferredAgeGroup_s.compare("20-30") == 0)
                                        tp.SetPreferredAgeGroup(1);
                                    else if (preferredAgeGroup_s.compare("30-40") == 0)
                                        tp.SetPreferredAgeGroup(2);
                                    else if (preferredAgeGroup_s.compare("40-50") == 0)
                                        tp.SetPreferredAgeGroup(3);
                                    else
                                        tp.SetPreferredAgeGroup(0); 
                                }
                                else
                                    tp.SetPreferredAgeGroup(0);
                            }
                            else
                                tp.SetPreferredAgeGroup(0);

                            // comfort lever
                            int comfortLevel_i = -1;
                            if (travel_preferences_json.HasMember("comfort_level"))
                            {
                                Value& comfortLevel_json = travel_preferences_json["comfort_level"];
                                if (comfortLevel_json.IsInt()) comfortLevel_i = comfortLevel_json.GetInt();   
                            }
                            tp.SetComfortLevel(comfortLevel_i);

                            // luggage
                            bool luggage_b = false;
                            if (travel_preferences_json.HasMember("luggage"))
                            {
                                Value& luggage_json = travel_preferences_json["luggage"];
                                if (luggage_json.IsBool()) luggage_b = luggage_json.GetBool();
                            }
                            tp.SetLuggage(luggage_b);

                            // GPS tracking
                            bool gpsTracking_b = false;
                            if (travel_preferences_json.HasMember("gps_tracking"))
                            {
                                Value& gpsTracking_json = travel_preferences_json["gps_tracking"];
                                if (gpsTracking_json.IsBool()) gpsTracking_b = gpsTracking_json.GetBool();
                            }
                            tp.SetGpsTracking(gpsTracking_b);

                            // food
                            bool food_b = false;
                            if (travel_preferences_json.HasMember("food"))
                            {
                                Value& food_json = travel_preferences_json["food"];
                                if (food_json.IsBool()) food_b = food_json.GetBool();
                            }
                            tp.SetFood(food_b);

                            // pets
                            bool pets_b = false;
                            if (travel_preferences_json.HasMember("pets"))
                            {
                                Value& pets_json = travel_preferences_json["pets"];
                                if (pets_json.IsBool()) pets_b = pets_json.GetBool();
                            }
                            tp.SetPets(pets_b);

                            // smoking
                            bool smoking_b = false;
                            if (travel_preferences_json.HasMember("smoking"))
                            {
                                Value& smoking_json = travel_preferences_json["smoking"];
                                if (smoking_json.IsBool()) smoking_b = smoking_json.GetBool();
                            }
                            tp.SetSmoking(smoking_b);

                            // music
                            bool music_b = false;
                            if (travel_preferences_json.HasMember("music"))
                            {
                                Value& music_json = travel_preferences_json["music"];
                                if (music_json.IsBool()) music_b = music_json.GetBool();
                            }
                            tp.SetMusic(music_b);

                            // maximum cost
                            int maxCost_i = -1;
                            if (travel_preferences_json.HasMember("max_cost"))
                            {
                                Value& maxCost_json = travel_preferences_json["max_cost"];
                                if (maxCost_json.IsInt()) maxCost_i = maxCost_json.GetInt();
                            }
                            tp.SetMaxCost(static_cast<double>(maxCost_i));

                            // maximum walk distance
                            int maxWalkDistance_i = -1;
                            if (travel_preferences_json.HasMember("max_walk_distance"))
                            {
                                Value& maxWalkDistance_json = travel_preferences_json["max_walk_distance"];
                                if (maxWalkDistance_json.IsInt()) maxWalkDistance_i = maxWalkDistance_json.GetInt();   
                            }
                            tp.SetMaxWalkDistance(static_cast<double>(maxWalkDistance_i));

                            // maximum number of transfers
                            int maxNumberOfTransfers_i = -1;
                            if (travel_preferences_json.HasMember("max_transfers"))
                            {
                                Value& maxNumberOfTransfers_json = travel_preferences_json["max_transfers"];
                                if (maxNumberOfTransfers_json.IsInt()) maxNumberOfTransfers_i = maxNumberOfTransfers_json.GetInt();
                            }
                            tp.SetMaxNumberOfTransfers(maxNumberOfTransfers_i);

                            if ((numOfValidUsers > k) && firstTime)
                            {
                                firstTime = false;
                                noData = false;
                            }
                            points.push_back(tp);

                        }
                        else continue;    
                    }
                    else continue;
                }
            }
        }
    }

    if (!noData)
    {
        // Create initial and final clusters
        for (int i = 0; i < k; i++)
        {
            Cluster* initial = new Cluster(i);
            initialClusters.push_back(initial);
            Cluster* final = new Cluster(i);
            finalClusters.push_back(final);
        }
    }
}

Kmeans::~Kmeans()
{
    if (points.size() > 0)
        points.clear();

    if (initialClusters.size() > 0)
	{
            for (size_t i = 0; i < initialClusters.size(); i++)
                delete initialClusters[i];
            initialClusters.clear();
	}
        
    if (finalClusters.size() > 0)
    {
        for (size_t i = 0; i < finalClusters.size(); i++)
            delete finalClusters[i];
        finalClusters.clear();
    }
       
    if (pointIDClusterIDAllocation.size() > 0)
        pointIDClusterIDAllocation.clear();

    if (clusterIDPointsOfClusterIDsAllocation.size() > 0)
        clusterIDPointsOfClusterIDsAllocation.clear();
}

/*! Choose randomly K points from the data to be the initial centroids for the beginning of the algorithm. */
void Kmeans::SetInitialClustersRandomly()
{
    int index;
    srand (time(NULL)); 
    for (int i = 0; i < k; i++)
    {
        index = rand() % points.size();
        initialClusters[i]->center = points[index];
    }
}

/*! Choose K points from the data to be the initial centroids for the beginning of the algorithm. */
void Kmeans::SetInitialClustersByInitialPoints()
{
    for (int i = 0; i < k; i++)
        initialClusters[i]->center = points[i];
}

/*! Put points in clusters. */
void Kmeans::SetPointsToClusters()
{
    double dist = 0.0;
    double minDist = 100000000.0;
    int minID = -1;
    for (size_t i = 0; i < points.size(); i++)
    {
        for (size_t j = 0; j < initialClusters.size(); j++)
        {
            TravelProfile center;
            center = initialClusters[j]->center;
            dist = mtdf::CalcDistanceOfPoints(points[i], center);
			//std::cout << dist << "\n";
            if (dist < minDist)
            {
                minDist = dist;
                minID = j;
            }
        }
        initialClusters[minID]->pointsOfCluster.push_back(&points[i]);
        minDist = 100000000.0;
        minID = -1;
    }
}

/*! Calculate new centroids */
void Kmeans::SetFinalClusters()
{
    for (int i = 0; i < k; i++)
    {
        if (initialClusters[i]->pointsOfCluster.size() != 0)
        {
            
            mtdf::CalculateAverageOfPoints(initialClusters[i], finalClusters[i]);
            
            //IntVector preferredTransportMeanVals; preferredTransportMeanVals.assign(4, 0);
            //IntVector carpoolerPreferredGenderVals; carpoolerPreferredGenderVals.assign(3, 0);
            //IntVector specialRequestVals; specialRequestVals.assign(5, 0);
            //IntVector optimisationVals; optimisationVals.assign(6, 0);
            //IntVector preferredAgeGroupVals; preferredAgeGroupVals.assign(4, 0);
            //IntVector comfortLevelVals; comfortLevelVals.assign(5, 0);
            //IntVector luggageVals; luggageVals.assign(2, 0);
            //IntVector gpsTrackingVals; gpsTrackingVals.assign(2, 0);
            //IntVector foodVals; foodVals.assign(2, 0);
            //IntVector petsVals; petsVals.assign(2, 0);
            //IntVector smokingVals; smokingVals.assign(2, 0);
            //IntVector musicVals; musicVals.assign(2, 0);

            //double meanMaxCost = 0.0;
            //double meanMaxWalkDistance = 0.0;
            //double meanMaxNumberOfTransfers = 0.0;

            //int n = initialClusters[i]->pointsOfCluster.size();

            //for (int j = 0 ; j < n ; j++)
            //{
            //    // nominal
            //    PreferredTransportMean ptm = initialClusters[i]->pointsOfCluster[j]->GetPreferredTransportMean();
            //    if (ptm == NO_PTM)
            //        preferredTransportMeanVals[NO_PTM]++;
            //    else if (ptm == CAR)
            //        preferredTransportMeanVals[CAR]++;
            //    else if (ptm == BUS)
            //        preferredTransportMeanVals[BUS]++;
            //    else if (ptm == WALK)
            //        preferredTransportMeanVals[WALK]++;

            //    CarpoolerPreferredGender cpg = initialClusters[i]->pointsOfCluster[j]->GetCarpoolerPreferredGender();

            //    if (cpg == NO_PG)
            //        carpoolerPreferredGenderVals[NO_PG]++;
            //    else if (cpg == MALE)
            //        carpoolerPreferredGenderVals[MALE]++;
            //    else if (cpg == FEMALE)
            //        carpoolerPreferredGenderVals[FEMALE]++;

            //    SpecialRequest sr = initialClusters[i]->pointsOfCluster[j]->GetSpecialRequest();

            //    if (sr == NO_SR)
            //        specialRequestVals[NO_SR]++;
            //    else if (sr == WHEELCHAIR)
            //        specialRequestVals[WHEELCHAIR]++;
            //    else if (sr == BLIND)
            //        specialRequestVals[BLIND]++;
            //    else if (sr == DEAF)
            //        specialRequestVals[DEAF]++;
            //    else if (sr == ELDERLY)
            //        specialRequestVals[ELDERLY]++;

            //    Optimisation opt = initialClusters[i]->pointsOfCluster[j]->GetOptimisation();

            //    if (opt == NO_OPT)
            //        optimisationVals[NO_OPT]++;
            //    else if (opt == FASTEST)
            //        optimisationVals[FASTEST]++;
            //    else if (opt == SHORTEST)
            //        optimisationVals[SHORTEST]++;
            //    else if (opt == CHEAPEST)
            //        optimisationVals[CHEAPEST]++;
            //    else if (opt == COMFORT)
            //        optimisationVals[COMFORT]++;
            //    else if (opt == SAFEST)
            //        optimisationVals[SAFEST]++;

            //    PreferredAgeGroup pag = initialClusters[i]->pointsOfCluster[j]->GetPreferredAgeGroup();

            //    if (pag == NO_PAG)
            //        preferredAgeGroupVals[NO_PAG]++;
            //    else if (pag == AGE_GROUP1)
            //        preferredAgeGroupVals[AGE_GROUP1]++;
            //    else if (pag == AGE_GROUP2)
            //        preferredAgeGroupVals[AGE_GROUP2]++;
            //    else if (pag == AGE_GROUP3)
            //        preferredAgeGroupVals[AGE_GROUP3]++;

            //    int cl = initialClusters[i]->pointsOfCluster[j]->GetComfortLevel();

            //    if (cl == 1)
            //        comfortLevelVals[0]++;
            //    else if (cl == 2)
            //        comfortLevelVals[1]++;
            //    else if (cl == 3)
            //        comfortLevelVals[2]++;
            //    else if (cl == 4)
            //        comfortLevelVals[3]++;
            //    else if (cl == 5)
            //        comfortLevelVals[4]++;

            //    bool lug = initialClusters[i]->pointsOfCluster[j]->GetLuggage();

            //    // binary
            //    if (!lug)
            //        luggageVals[0]++;
            //    else
            //        luggageVals[1]++;

            //    bool gpsTrack = initialClusters[i]->pointsOfCluster[j]->GetGpsTracking();

            //    if (!gpsTrack)
            //        gpsTrackingVals[0]++;
            //    else
            //        gpsTrackingVals[1]++;

            //    bool food = initialClusters[i]->pointsOfCluster[j]->GetFood();

            //    if (!food)
            //        foodVals[0]++;
            //    else
            //        foodVals[1]++;

            //    bool pets = initialClusters[i]->pointsOfCluster[j]->GetPets();

            //    if (!pets)
            //        petsVals[0]++;
            //    else
            //        petsVals[1]++;

            //    bool smoking = initialClusters[i]->pointsOfCluster[j]->GetSmoking();

            //    if (!smoking)
            //        smokingVals[0]++;
            //    else
            //        smokingVals[1]++;

            //    bool music = initialClusters[i]->pointsOfCluster[j]->GetMusic();

            //    if (!music)
            //        musicVals[0]++;
            //    else
            //        musicVals[1]++;

            //    // ordinal and continuous
            //    meanMaxCost += initialClusters[i]->pointsOfCluster[j]->getMaxCost();
            //    meanMaxWalkDistance += initialClusters[i]->pointsOfCluster[j]->GetMaxWalkDistance();
            //    meanMaxNumberOfTransfers += (double)(initialClusters[i]->pointsOfCluster[j]->GetMaxNumberOfTransfers());
            //}

            //int preferredTransportMeanVal = std::max_element(preferredTransportMeanVals.begin(), preferredTransportMeanVals.end()) - preferredTransportMeanVals.begin();
            //preferredTransportMeanVals.clear();
            //int carpoolerPreferredGenderVal = std::max_element(carpoolerPreferredGenderVals.begin(), carpoolerPreferredGenderVals.end()) - carpoolerPreferredGenderVals.begin();
            //carpoolerPreferredGenderVals.clear();
            //int specialRequestVal = std::max_element(specialRequestVals.begin(), specialRequestVals.end()) - specialRequestVals.begin();
            //specialRequestVals.clear();
            //int optimisationVal = std::max_element(optimisationVals.begin(), optimisationVals.end()) - optimisationVals.begin();
            //optimisationVals.clear();
            //int preferredAgeGroupVal = std::max_element(preferredAgeGroupVals.begin(), preferredAgeGroupVals.end()) - preferredAgeGroupVals.begin();
            //preferredAgeGroupVals.clear();
            //int comfortLevelVal = std::max_element(comfortLevelVals.begin(), comfortLevelVals.end()) - comfortLevelVals.begin();
            //comfortLevelVals.clear();
            //int luggageVal = std::max_element(luggageVals.begin(), luggageVals.end()) - luggageVals.begin();
            //luggageVals.clear();
            //int gpsTrackingVal = std::max_element(gpsTrackingVals.begin(), gpsTrackingVals.end()) - gpsTrackingVals.begin();
            //gpsTrackingVals.clear();
            //int foodVal = std::max_element(foodVals.begin(), foodVals.end()) - foodVals.begin();
            //foodVals.clear();
            //int petsVal = std::max_element(petsVals.begin(), petsVals.end()) - petsVals.begin();
            //petsVals.clear();
            //int smokingVal = std::max_element(smokingVals.begin(), smokingVals.end()) - smokingVals.begin();
            //smokingVals.clear();
            //int musicVal = std::max_element(musicVals.begin(), musicVals.end()) - musicVals.begin();
            //musicVals.clear();
            //meanMaxCost /= (double)n;
            //meanMaxWalkDistance /= (double)n;
            //meanMaxNumberOfTransfers /= (double)n;

            //TravelProfile tp;
            //
            //tp.SetPreferredTransportMean(preferredTransportMeanVal);
            //tp.SetCarpoolerPreferredGender(carpoolerPreferredGenderVal);
            //tp.SetSpecialRequest(specialRequestVal);
            //tp.SetOptimisation(optimisationVal);
            //tp.SetPreferredAgeGroup(preferredAgeGroupVal);
            //tp.SetComfortLevel(comfortLevelVal);

            //tp.SetLuggage(!(luggageVal == 0));
            //tp.SetGpsTracking(!(gpsTrackingVal == 0));
            //tp.SetFood(!(foodVal == 0));
            //tp.SetPets(!(petsVal == 0));
            //tp.SetSmoking(!(smokingVal == 0));
            //tp.SetMusic(!(musicVal == 0));

            //tp.SetMaxNumberOfTransfers(meanMaxNumberOfTransfers);
            //tp.SetMaxCost(meanMaxCost);
            //tp.SetMaxWalkDistance(meanMaxWalkDistance);
            
            //finalClusters[i]->center = tp;
            for (size_t m = 0; m < initialClusters[i]->pointsOfCluster.size(); m++)
                finalClusters[i]->pointsOfCluster.push_back(initialClusters[i]->pointsOfCluster[m]);          
        }
    }
}

/*Check if the algorithm converged.At the end of an iteration,the centers of the clusters are the same
with the centers of the initial clusters then it means that during the iteration the assignment of points
in the clusters didn't change so the algorithm converged.
*/
bool Kmeans::IsOver()
{
    for (int i = 0; i < k; i++)
        if (!(initialClusters[i]->center == finalClusters[i]->center)) return false;
    return true;
}

void Kmeans::Initialize()
{
    for (int i = 0; i < k; i++)
    {
        initialClusters[i]->pointsOfCluster.clear();
        finalClusters[i]->pointsOfCluster.clear();
        initialClusters[i]->center = finalClusters[i]->center;
    }
}

void Kmeans::RunKmeans()
{
    // First iteration
    int it = 1;
    SetInitialClustersRandomly();
    SetPointsToClusters();
    SetFinalClusters();
    //double wcss = calculateWCSS();
    //std::cout << "Iteration: " << it << " , WCSS: " << wcss << "\n";
    // Next iterations
    while ((!IsOver()) && (it <= numOfIterations))
    {
        it++;		
        Initialize();
        SetPointsToClusters();
        SetFinalClusters();
        //wcss = calculateWCSS();
        //std::cout << "Iteration: " << it << " , WCSS: " << wcss << "\n";
    }
    //std::cout << "Clustering finished in " << it - 1 << " iterations.\n";
}

void Kmeans::WriteCentroidsToFile(std::string centroidsFilename)
{
    std::ofstream out;
    out.open(centroidsFilename);
    if (out.is_open())
    {
        for (size_t i = 0; i < finalClusters.size(); i++)
        {
            finalClusters[i]->WriteCentroidToFile(out);
            out << "\n";
        }
        out.close();
    }
}

void Kmeans::CreatePointIDClusterIDAllocation()
{
    for (size_t i = 0; i < finalClusters.size(); i++)
    {
        for (size_t j = 0; j < finalClusters[i]->pointsOfCluster.size(); j++)
            pointIDClusterIDAllocation.insert(std::make_pair(finalClusters[i]->pointsOfCluster[j]->GetID(), finalClusters[i]->GetID())); // (PointID,ClusterID)
    }
}

void Kmeans::CreateClusterIDPointsOfClusterIDsAllocation()
{
    for (size_t i = 0; i < finalClusters.size(); i++)
    {
        StringVector pointsOfClusterIDs;
        for (size_t j = 0; j < finalClusters[i]->pointsOfCluster.size(); j++)
            pointsOfClusterIDs.push_back(finalClusters[i]->pointsOfCluster[j]->GetID());
        clusterIDPointsOfClusterIDsAllocation.insert(std::make_pair(finalClusters[i]->GetID(), pointsOfClusterIDs));
        pointsOfClusterIDs.clear();
    }
}

void Kmeans::WriteClusterIDPointsOfClusterIDsAllocationToFile(std::string allocationFilename1)
{
    std::ofstream out;
    out.open(allocationFilename1);
    if (out.is_open())
    {
        for (auto it = clusterIDPointsOfClusterIDsAllocation.begin(); it != clusterIDPointsOfClusterIDsAllocation.end(); ++it)
        {
            int clusterID = it->first;
            StringVector pointsOfClusterIDs = it->second;
            out << clusterID;
            for (size_t i = 0 ; i < pointsOfClusterIDs.size() ; i++)
                out << " " << pointsOfClusterIDs[i];
            out << "\n";
            pointsOfClusterIDs.clear();
        } 	
        out.close();
    }
}

void Kmeans::WritePointIDClusterIDAllocationToFile(std::string allocationFilename2)
{
    std::ofstream out;
    out.open(allocationFilename2);
    if (out.is_open())
    {
        for (auto it = pointIDClusterIDAllocation.begin() ; it != pointIDClusterIDAllocation.end() ; ++it)
        {
            std::string pointID = it->first;
            int clusterID = it->second;
            out << pointID << " " << clusterID << "\n";
        }
        out.close();
    }
}

//double Kmeans::calculateSilhouette()
//{	
//	DoubleVector silhouettes;
//	for (int i = 0 ; i < points.size() ; i++)
//	{
//		double a_for_point, final_b_for_point, temp_b, silhouetteForPoint;
//	//	std::cout << "Calculating the average dissimilarity of point " << points[i].GetID() << " of all other data within the same cluster..." << "\n";
//		a_for_point = 0;
//		int clusterID = -1;
//		auto it = pointIDClusterIDAllocation.find(points[i].GetID());
//		if (it != pointIDClusterIDAllocation.end())
//			clusterID = it->second;
//
//		for (int j = 0 ; j < finalClusters[clusterID].getNumOfPointsInCluster() ; j++)
//		{
//			Point* pointOfCluster = finalClusters[clusterID].getPointOfCluster(j);
//			a_for_point += mf::findEuclideanDistanceOfPoints(points[i], *pointOfCluster);
//		}
//		a_for_point /= finalClusters[clusterID].getNumOfPointsInCluster();
//
//
//	//	std::cout << "Calculating the lowest average dissimilarity of point " << points[i].GetID() << " of all other data of all other clusters..." << "\n";
//		DoubleVector b_for_point;
//		for (int j = 0 ; j < finalClusters.size() ; j++)
//		{
//			if(finalClusters[j].GetID() != clusterID)
//			{
//				temp_b = 0;
//				for(int k = 0 ; k < finalClusters[j].getNumOfPointsInCluster() ; k++)
//				{	
//					Point* pointOfCluster = finalClusters[j].getPointOfCluster(k);
//					temp_b += mf::findEuclideanDistanceOfPoints(points[i], *pointOfCluster);
//				}
//				temp_b /= finalClusters[j].pointsOfCluster.size();
//				b_for_point.push_back(temp_b);
//			}
//		}
//		final_b_for_point = *std::min_element(b_for_point.begin(), b_for_point.end());
//		b_for_point.clear();
//
//	//	std::cout << "Calculating the silhouette of point " << points[i].GetID() <<"\n";
//		silhouetteForPoint = (final_b_for_point - a_for_point)/std::max(a_for_point, final_b_for_point);
//		silhouettes.push_back(silhouetteForPoint);
//	}
//
//	double silhouette = 0.0;
//	for(int i = 0 ; i < silhouettes.size() ; i++)
//		silhouette += silhouettes[i];
//	silhouette /= (double)silhouettes.size();
//	
//	return silhouette;
//}


double Kmeans::CalculateWCSS()
{
    double withinClusterVariance = 0.0;
    for (size_t i = 0; i < finalClusters.size(); i++)
    {
        for (size_t j = 0; j < finalClusters[i]->pointsOfCluster.size(); j++)
        {
            TravelProfile* pointOfCluster = finalClusters[i]->pointsOfCluster[j];
            TravelProfile center = finalClusters[i]->center;
            withinClusterVariance += mtdf::CalcDistanceOfPoints(*pointOfCluster, center);
        }
    }
    return withinClusterVariance;
}


//double Kmeans::calculateDaviesBouldinIndex()
//{
//	double DaviesDoublinIndex = 0.0;
//	DoubleVector AverageIntraClusterDistances;
//	DoubleVector2D InterClusterDistances;
//	for (int i = 0 ; i < finalClusters.size() ; i++)
//	{
//		double averageIntaClusterDistance = 0.0;
//		for (int j = 0 ; j < finalClusters[i].getNumOfPointsInCluster() ; j++)
//		{
//			Point* pointOfCluster = finalClusters[i].getPointOfCluster(j);
//			Point center = finalClusters[i].getCenter();
//			averageIntaClusterDistance+= mf::findEuclideanDistanceOfPoints(*pointOfCluster, center);
//		}
//		averageIntaClusterDistance /= finalClusters[i].getNumOfPointsInCluster();
//		AverageIntraClusterDistances.push_back(averageIntaClusterDistance);
//	}
//
//	for (int i = 0 ; i < finalClusters.size() ; i++)
//	{
//		DoubleVector temp;
//		double interClusterDistance;
//		Point center1 = finalClusters[i].getCenter();
//		for (int j = 0 ; j < finalClusters.size() ; j++)
//		{
//			Point center2 = finalClusters[j].getCenter();
//			interClusterDistance = mf::findEuclideanDistanceOfPoints(center1, center2);
//			temp.push_back(interClusterDistance);
//		}
//		InterClusterDistances.push_back(temp);
//	}
//
//	for (int i = 0 ; i < finalClusters.size() ; i++)
//	{
//		double Di;
//		double maxDi = -1.0;
//		for (int j = 0 ; j < finalClusters.size() ; j++)
//		{
//			if (i!=j)
//			{
//				Di = (AverageIntraClusterDistances[i]+AverageIntraClusterDistances[j]) / InterClusterDistances[i][j];
//				if(Di > maxDi) maxDi = Di;
//			}
//		}
//		DaviesDoublinIndex += maxDi;
//	}
//	DaviesDoublinIndex /= finalClusters.size();
//
//	return DaviesDoublinIndex;
//}

void Kmeans::CalculateClusterDistances(std::string distancesFilename)
{
    std::ofstream out;
    out.open(distancesFilename);
    if (out.is_open())
    {
        for (size_t i = 0; i < finalClusters.size(); i++)
        {
            for (size_t j = 0; j < finalClusters.size(); j++)
            {
                out << mtdf::CalcDistanceOfPoints(finalClusters[i]->center, finalClusters[j]->center);
                out << " ";
            }
            out << "\n";
        }
        out.close();
    }
} 