/* 
 * File:   main.cpp
 * Author: asal
 *
 * Created on January 10, 2017, 11:39 AM
 */

#include "PropertiesParser.h"
#include "Kmeans.h"

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

int main(int argc, char** argv)
{
    if (argc == 4)
    {
        // get current timestamp
        time_t rawtime;
        time (&rawtime);
        struct tm * timeinfo;
        timeinfo = localtime(&rawtime);
        std::cout << "Current time: " << timeinfo->tm_mday << "/" << timeinfo->tm_mon + 1 << "/" << timeinfo->tm_year + 1900 << " "
            << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << std::endl;

        int k = stoi(std::string(argv[1]));
        int numOfIterations = stoi(std::string(argv[2]));
        std::string BASE_URL = std::string(argv[3]);

        // clustering 
        Kmeans* kmeans_instance = new Kmeans(k, numOfIterations, BASE_URL);
        if ((!kmeans_instance->GetNoData()) && (kmeans_instance->GetNumOfPoints() > k))
        {
            kmeans_instance->RunKmeans();
            kmeans_instance->CreatePointIDClusterIDAllocation();
            kmeans_instance->WritePointIDClusterIDAllocationToFile(GetExecutablePathAndMatchItWithFilename("clustersAllocation.txt"));
            kmeans_instance->CalculateClusterDistances(GetExecutablePathAndMatchItWithFilename("clustersDistances.txt"));
            std::cout << "Clusters created." << std::endl;
        }
        else
        {
            std::ofstream out;
            out.open(GetExecutablePathAndMatchItWithFilename("clustersAllocation.txt"));
            for (size_t i = 0; i < kmeans_instance->points.size(); i++)
                out << kmeans_instance->points[i].GetID() << " " << 0 << "\n";
            out.close();

            out.open(GetExecutablePathAndMatchItWithFilename("clustersDistances.txt"));
            out << 0;
            out.close();
            std::cout << "Clusters not created. All users in 1 cluster with id 0." << std::endl;
        }
        delete kmeans_instance;
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Wrong number of arguments. 3 arguments must be provided: number of clusters, number of iterations for k-means to converge, BASE_URL" << std::endl;
        std::cout << std::endl;
    }
            
    return 0;
}

