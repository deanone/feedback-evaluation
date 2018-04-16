/* 
 * File:   main.cpp
 * Author: asal
 *
 * Created on February 16, 2017, 12:45 PM
 */

#include <iomanip>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "WebService.h"
#include "PropertiesParser.h"
#include "DataTypes.h"
#include "Rating.h"
#include "Reputation.h"

using namespace rapidjson;

bool AreEqual(const double d1, const double d2)
{
    if (std::fabs(d1 - d2) < std::numeric_limits<double>::min())
        return true;
    else 
        return false;
}

std::string GetExecutablePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

std::string GetExecutablePathAndMatchItWithFilename(std::string fileName)
{
    std::string execPath = GetExecutablePath();
    size_t found = execPath.find_last_of("/");
    execPath = execPath.substr(0, found);
    std::stringstream ss;
    ss << execPath << "/" << fileName;
    return ss.str();
}

void LoadClustersAllocation(std::map<std::string, int>& clusterAllocation)
{
    std::string dataline;
    std::string clusterAllocationFile = GetExecutablePathAndMatchItWithFilename("clustersAllocation.txt");
    std::ifstream in;
    in.open(clusterAllocationFile);
    if (in.is_open())
    {
        while (std::getline(in, dataline))
        {
            std::stringstream ss(dataline);
            std::string item;
            StringVector items;
            while (std::getline(ss, item, ' '))
                items.push_back(item);
            std::string userID = items[0];
            int clusterID = stoi(items[1]);
            items.clear();
            clusterAllocation.insert(std::make_pair(userID, clusterID));
        }
        in.close();
    }
}

void LoadClustersDistances(DoubleVector2D& clustersDistances)
{
    std::string clustersDistancesFile = GetExecutablePathAndMatchItWithFilename("clustersDistances.txt");
    std::string dataline;
    std::ifstream in;
    in.open(clustersDistancesFile);
    if (in.is_open())
    {
        while (getline(in, dataline))
        {
            std::stringstream ss(dataline);
            std::string item;
            StringVector items;
            while (getline(ss, item, ' '))
                items.push_back(item);
            DoubleVector temp;
            for (size_t i = 0; i < items.size(); i++)
                temp.push_back((double)stof(items[i]));
            items.clear();
            clustersDistances.push_back(temp);
            temp.clear();
        }
        in.close();
    }
}

int LoadReputations(std::map<std::string, Reputation*>& reputations, std::string BASE_URL)
{
    WebService* srv = new WebService();
    std::string response = "";
    response = srv->GetReputations(BASE_URL);
    delete srv;
    
    if (response.compare("Failed to query.") != 0)
    {    
        Document d;
        d.Parse(response.c_str());
        if (d.IsObject() && d.HasMember("reputations"))
        {
            Value& reputations_json = d["reputations"];
            if (reputations_json.IsArray() && reputations_json.Size() > 0)
            {
                bool hasReputations = false;
                bool firstTime = true;
                for (SizeType i = 0; i < reputations_json.Size(); i++)
                {
                    if (reputations_json[i].IsObject() && reputations_json[i].HasMember("user_id") && reputations_json[i].HasMember("reputation")
                       && reputations_json[i].HasMember("r") && reputations_json[i].HasMember("s") && reputations_json[i].HasMember("last_update") 
                       && reputations_json[i].HasMember("_id"))
                    {
                        // _id
                        std::string _id_s = "";
                        Value& _id_json = reputations_json[i]["_id"];
                        if (_id_json.IsString()) _id_s = _id_json.GetString();
                        else continue;

                        // user_id                
                        std::string user_id_s = "";
                        Value& user_id_json = reputations_json[i]["user_id"];
                        if (user_id_json.IsString()) user_id_s = user_id_json.GetString();
                        else continue;

                        // reputation
                        int reputation = -1;
                        Value& reputation_json = reputations_json[i]["reputation"];
                        if (reputation_json.IsInt()) reputation = reputation_json.GetInt();
                        else continue;

                        // r
                        int r = -1;
                        Value& r_json = reputations_json[i]["r"];
                        if (r_json.IsInt()) r = r_json.GetInt();
                        else continue;

                        // s
                        int s = -1;
                        Value& s_json = reputations_json[i]["s"];
                        if (s_json.IsInt()) s = s_json.GetInt();
                        else continue;

                        // lastUpdate
                        int lastUpdate = -1;
                        Value& lastUpdate_json = reputations_json[i]["last_update"];
                        if (lastUpdate_json.IsInt()) lastUpdate = lastUpdate_json.GetInt();
                        else continue;

                        Reputation* Rep_p = new Reputation(r, s, reputation, lastUpdate, _id_s);       
                        reputations.insert(std::make_pair(user_id_s, Rep_p));

                        if (firstTime)
                        {
                            firstTime = false;
                            hasReputations = true;
                        }
                    }
                }
                if (hasReputations)
                    return 0;   // everything OK
                else
                    return 3;   // error code, there is no object to have all the necessary fields, i.e. "_id", "users_id", "r", "s", "reputation", "last_update" and with the correct types        
            }
            else return 2;  // error code, no reputations available
        }
        else return 2;  // error code, no reputations available
    }
    else return 1;   // error code, connection error
}

int LoadRatings(std::map<std::string, std::vector<Rating*> >& Ratings, std::string BASE_URL, long int timestamp)
{
    WebService* srv = new WebService();
    std::string response = "";
    response = srv->GetRatings(BASE_URL, timestamp);
    delete srv;
    
    if (response.compare("Failed to query.") != 0)
    {
        Document d;
        d.Parse(response.c_str());
        if (d.IsObject() && d.HasMember("feedbacks"))
        {
            Value& feedbacks_json = d["feedbacks"];
            if (feedbacks_json.IsArray() && feedbacks_json.Size() > 0)
            {
                bool hasRatings = false;
                bool firstTime = true;
                for (SizeType i = 0; i < feedbacks_json.Size(); i++)
                {
                    if (feedbacks_json[i].IsObject() && feedbacks_json[i].HasMember("reviewer_id") && feedbacks_json[i].HasMember("reviewed_id")
                       && feedbacks_json[i].HasMember("date") && feedbacks_json[i].HasMember("ratings"))
                    {
                        // reviewer_id: the id of the user that made the review
                        std::string reviewer_id_s = "";
                        Value& reviewer_id_json = feedbacks_json[i]["reviewer_id"];
                        if (reviewer_id_json.IsString()) reviewer_id_s = reviewer_id_json.GetString();
                        else continue;

                        // reviewed_id: the id of the user for whom the review is about
                        std::string reviewed_id_s = "";
                        Value& reviewed_id_json = feedbacks_json[i]["reviewed_id"];
                        if (reviewed_id_json.IsString()) reviewed_id_s = reviewed_id_json.GetString();
                        else continue;

                        // date: when the review was submitted
                        int date = -1;
                        Value& date_json = feedbacks_json[i]["date"];
                        if (date_json.IsInt()) date = date_json.GetInt();
                        else continue;

                        // rating features
                        Value& ratings_json = feedbacks_json[i]["ratings"];
                        if (ratings_json.IsObject() && (ratings_json.HasMember("driving_behaviour") || ratings_json.HasMember("comfort_level")
                           || ratings_json.HasMember("route") || ratings_json.HasMember("satisfaction_level") || ratings_json.HasMember("carpooler_behaviour")))
                        {
                            // driving behavior
                            int driving_behaviour_i = -1;
                            if (ratings_json.HasMember("driving_behaviour"))
                            {
                                Value& driving_behaviour_json = ratings_json["driving_behaviour"];
                                if (driving_behaviour_json.IsInt()) driving_behaviour_i = driving_behaviour_json.GetInt(); 
                            }

                            // comfort level
                            int comfort_level_i = -1;
                            if (ratings_json.HasMember("comfort_level"))
                            {
                                Value& comfort_level_json = ratings_json["comfort_level"];
                                if (comfort_level_json.IsInt()) comfort_level_i = comfort_level_json.GetInt();
                            }

                            // route
                            int route_i = -1;
                            if (ratings_json.HasMember("route"))
                            {
                                Value& route_json = ratings_json["route"];
                                if (route_json.IsInt()) route_i = route_json.GetInt();
                            }

                            // satisfaction level
                            int satisfaction_level_i = -1;
                            if (ratings_json.HasMember("satisfaction_level"))
                            {
                                Value& satisfaction_level_json = ratings_json["satisfaction_level"];
                                if (satisfaction_level_json.IsInt()) satisfaction_level_i = satisfaction_level_json.GetInt();
                            }

                            // carpooler behaviour
                            int carpooler_behaviour_i = -1;
                            if (ratings_json.HasMember("carpooler_behaviour"))
                            {
                                Value& carpooler_behaviour_json = ratings_json["carpooler_behaviour"];
                                if (carpooler_behaviour_json.IsInt()) carpooler_behaviour_i = carpooler_behaviour_json.GetInt();   
                            }

                            Rating* r = new Rating(reviewer_id_s, reviewed_id_s);
                            r->AddRatingVal(driving_behaviour_i);
                            r->AddRatingVal(comfort_level_i);
                            r->AddRatingVal(route_i);
                            r->AddRatingVal(satisfaction_level_i);
                            r->AddRatingVal(carpooler_behaviour_i);

                            auto it = Ratings.find(reviewed_id_s);
                            if (it == Ratings.end())
                            {
                                std::vector<Rating*> temp;
                                temp.push_back(r);
                                Ratings.insert(std::make_pair(reviewed_id_s, temp));
                                temp.clear();
                            }
                            else
                                it->second.push_back(r);

                            if (firstTime)
                            {
                                firstTime = false;
                                hasRatings = true;
                            }
                        }                        
                    }
                }
                if (hasRatings)
                    return 0;   // everything OK
                else
                    return 3;   // error code, there is no object to have all the necessary fields, i.e. "reviewer_id", "reviewed_id", "date", "ratings"           
            }
            else return 2;  // error code, no feadbacks available
        }
        else return 2;  // error code, no feadbacks available 
    }
    else return 1;  // error code, connection error
}

//void UpdateReputations(std::map<std::string, Reputation*>& reputations, std::string BASE_URL)
//{
//    // get current timestamp
//    time_t rawtime;
//    time (&rawtime);
//    struct tm * timeinfo;
//    timeinfo = localtime(&rawtime);
//    int last_update = mktime(timeinfo);
//      
//    // update reputation in MongoDB
//    WebService* srv = new WebService();
//    std::string response = "";
//    response = srv->GetReputations(BASE_URL);
//    delete srv;
//                
//    Document d;
//    d.Parse(response.c_str());
//    
//    if (d.IsObject() && d.HasMember("reputations"))
//    {
//        Value& reputations_json = d["reputations"];
//        if (reputations_json.IsArray())
//        {
//            for (SizeType i = 0; i < reputations_json.Size(); i++)
//            {
//                if (reputations_json[i].IsObject() && reputations_json[i].HasMember("user_id") && reputations_json[i].HasMember("_id"))
//                {
//                    // user_id
//                    std::string user_id_s = "";
//                    Value& user_id_json = reputations_json[i]["user_id"];
//                    if (user_id_json.IsString()) user_id_s = user_id_json.GetString();
//                    else continue;
//
//                    // _id
//                    std::string id_s = "";
//                    Value& id_json = reputations_json[i]["_id"];
//                    if (id_json.IsString()) id_s = id_json.GetString();
//                    else continue;
//                    
//                    auto it = reputations.find(user_id_s);
//                    if (it != reputations.end())
//                    {
//                        int r = it->second->GetR();
//                        int s = it->second->GetS();
//                        double Rep = it->second->GetRep();
//
//                        // reputation
//                        Value v1;
//                        v1.SetDouble(Rep);
//                        reputations_json[i]["reputation"] = v1;
//
//                        // r
//                        Value v2;
//                        v2.SetInt(r);
//                        reputations_json[i]["r"] = v2;
//
//                        // s
//                        Value v3;
//                        v3.SetInt(s);
//                        reputations_json[i]["s"] = v3;
//
//                        // user_id
//                        Value v4;
//                        v4.SetString(StringRef(user_id_s.c_str(), user_id_s.length()));
//                        reputations_json[i]["user_id"] = v4;
//
//                        // _id
//                        Value v5;
//                        v5.SetString(StringRef(id_s.c_str(), id_s.length()));
//                        reputations_json[i]["_id"] = v5;
//
//                        // last_update
//                        Value v6;
//                        v6.SetInt(last_update);
//                        reputations_json[i]["last_update"] = v6;
//
//                        rapidjson::StringBuffer buffer;
//                        buffer.Clear();
//                        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
//                        reputations_json[i].Accept(writer);
//                        std::string newUserReputationRecord =  buffer.GetString();
//
//                        WebService* srv2 = new WebService();
//                        std::string response2 = srv2->PutReputation(BASE_URL, id_s, newUserReputationRecord);
//                        delete srv2;
//                    }               
//                }
//            }
//        }
//    }
//}

void UpdateReputations(std::map<std::string, Reputation*>& reputations, std::string BASE_URL)
{
    for (auto it = reputations.begin(); it != reputations.end(); ++it)
    {
        rapidjson::Document document;
        document.SetObject();
        rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
        rapidjson::Value s1, s2;
        s1 = StringRef(it->first.c_str());  // user_id
        std::string _id_s = it->second->Get_id();
        s2 = StringRef(_id_s.c_str());   // _id
        
        document.AddMember("user_id", s1, allocator);
        document.AddMember("_id", s2, allocator);
        document.AddMember("r", it->second->GetR(), allocator);
        document.AddMember("s",it->second->GetS(), allocator);
        document.AddMember("reputation", it->second->GetRep(), allocator);
        document.AddMember("last_update", it->second->GetLastUpdate(), allocator);
        
        StringBuffer strbuf;
        Writer<StringBuffer> writer(strbuf);
        document.Accept(writer);
        std::string newUserReputationRecord =  strbuf.GetString();
        //std::cout << newUserReputationRecord << "\n";
        WebService* srv = new WebService();
        std::string response = srv->PutReputation(BASE_URL, _id_s, newUserReputationRecord);
        delete srv;
    }
}

int main(int argc, char** argv) 
{   
    if (argc == 3)
    {
        // get current timestamp
        time_t rawtime;
        time (&rawtime);
        struct tm * timeinfo;
        timeinfo = localtime(&rawtime);
        long int NOW = mktime(timeinfo);
        std::cout << "Current time: " << timeinfo->tm_mday << "/" << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_year + 1900 << " "
                                << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "\n";
        
        int numOfMinutesForWhichToConsiderFeedbacks = stoi(std::string(argv[1]));
        std::string BASE_URL = std::string(argv[2]);
        
        // Load input 1
        std::map<std::string, int> clusterAllocation;
        LoadClustersAllocation(clusterAllocation);

        // Load input 2
        DoubleVector2D clustersDistances;
        LoadClustersDistances(clustersDistances);

        // Load input 3
        std::map<std::string, Reputation*> reputations;
        int returnVal1 = LoadReputations(reputations, BASE_URL);

        // Load input 4
        std::map<std::string, std::vector<Rating*> > Ratings;
        long int timestamp = NOW - (numOfMinutesForWhichToConsiderFeedbacks * 60);
        int returnVal2 = LoadRatings(Ratings, BASE_URL, timestamp);
        
        // if reputations and ratings exist
        if ((returnVal1 == 0) && (returnVal2 == 0))
        {
            // Reputation calculation process
            for (auto it1 = Ratings.begin(); it1 != Ratings.end(); ++it1)
            {
                std::string reviewedID = it1->first;
                auto it2 = clusterAllocation.find(reviewedID);
                auto it3 = reputations.find(reviewedID);

                if (it2 != clusterAllocation.end() && it3 != reputations.end())
                {
                    // reviewed user's info
                    std::string user_id = it3->first;
                    int r = it3->second->GetR();
                    int s = it3->second->GetS();
                    int Rep_i = it3->second->GetRep();
                    int last_update = it3->second->GetLastUpdate();
                    std::string _id = it3->second->Get_id();
                    if ((user_id.compare("") == 0) || !(_id.compare("") == 0) || (r == -1) || (s == -1) || (Rep_i == -1) || (last_update == -1))
                        continue;
                    else
                    {
                        int reviewedClusterID = it2->second;
                        double maxDist = *max_element(clustersDistances[reviewedClusterID].begin(), clustersDistances[reviewedClusterID].end());
                        double totalRating = 0.0;

                        // process all the reviews for the specific reviewed user
                        for (size_t i = 0; i < it1->second.size(); i++)
                        {
                            std::string reviewerID = it1->second[i]->GetReviewerID();
                            auto it4 = clusterAllocation.find(reviewerID);
                            if (it4 != clusterAllocation.end())
                            {
                                int reviewerClusterID = it4->second;
                                it1->second[i]->CalculateMeanRating();
                                double dist = clustersDistances[reviewedClusterID][reviewerClusterID];
                                double w = 1.0;
                                if (maxDist != 0.0)
                                    w -= (dist / maxDist);
                                totalRating += (w * (it1->second[i]->GetMeanRating()));
                            }
                        }

                        totalRating /= static_cast<double>(it1->second.size());
                        int rOld = r;
                        int sOld = s;
                        if (totalRating >= 2.0) // feedback == 1.0
                            r++;
                        else    // feedback == -1.0
                            s++;

                        std::cout << "User: " << reviewedID << " --- " << "Old reputation: " << rOld << ", " << sOld << ", " << Rep_i << " --- ";
                        double Rep = static_cast<double>(r + 1) / static_cast<double>(r + s + 2);
                        Rep *= 5.0;
                        Rep = std::round(Rep);
                        Rep_i = static_cast<int>(Rep);
                        std::cout << "New reputation: " << r << ", " << s << ", " << Rep_i;
                        std::cout << std::endl;

                        it3->second->SetR(r);
                        it3->second->SetS(s);

                        it3->second->SetRep(Rep_i);
                        it3->second->SetLastUpdate(NOW);
                    }
                }    
            }
                        
            // update reputations
            UpdateReputations(reputations, BASE_URL);
        }
        else
        {
            if ((returnVal1 != 0) && (returnVal2 != 0))
                std::cout << "No reputations, no feedbacks available" << std::endl;
            else if (returnVal1 != 0)
                std::cout << "No reputations available" << std::endl;
            else
                std::cout << "No feedbacks available" << std::endl;       
        }
        
        std::cout << std::endl;
        
        // clean
        if (clusterAllocation.size() > 0)
            clusterAllocation.clear();
        if (clustersDistances.size() > 0)
            clustersDistances.clear();
        
        if (reputations.size() > 0)
        {
            for (auto it = reputations.begin(); it != reputations.end(); ++it)
                delete it->second;
            reputations.clear();
        }
        
        if (Ratings.size() > 0)
        {
            for (auto it = Ratings.begin(); it != Ratings.end(); ++it)
            {
                for (size_t i = 0; i < it->second.size(); i++)
                    delete it->second[i];
                it->second.clear();
            }
            Ratings.clear();
        }
    }
    else
    {
        std::cout << "Wrong number of arguments. 2 arguments must be provided: # last minutes for which to consider feedbacks, BASE_URL" << std::endl;
        std::cout << std::endl;
    }
    
    
    // checking ssh key
    return 0;
}

