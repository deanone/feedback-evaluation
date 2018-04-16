#include "Cluster.h"

Cluster::Cluster(int id) : ID(id)
{
}

Cluster::~Cluster()
{
//    if (pointsOfCluster.size() > 0)
//        pointsOfCluster.clear();
}

//void Cluster::setPointsToCluster(TravelProfile *p)
//{
//    pointsOfCluster.push_back(p);
//}

//int Cluster::getNumOfPointsInCluster()
//{
//    return pointsOfCluster.size();
//}

//TravelProfile* Cluster::getPointOfCluster(int index)
//{
//    if (index >= 0 && index < pointsOfCluster.size())
//        return pointsOfCluster[index];
//}

//void Cluster::clearPointsOfCluster()
//{
//    pointsOfCluster.clear();
//}

bool Cluster::operator==(Cluster &c)
{
    if (center == c.center) return true;
        return false;
}

void Cluster::PrintCentroidInConsole()
{
    std::cout << ID;
    center.PrintValuesToConsole();
}

void Cluster::PrintAllocationInConsole()
{
    for (int i = 0; i < pointsOfCluster.size(); i++)
        std::cout << pointsOfCluster[i]->GetID() << " " << ID << "\n";
}

void Cluster::WriteCentroidToFile(std::ostream &out)
{
    out << ID;
    center.WriteValuesToFile(out);
}

void Cluster::WriteAllocationToFile(std::ostream &out)
{
    for (int i = 0; i < pointsOfCluster.size(); i++)
        out << pointsOfCluster[i]->GetID() << " " << ID << "\n";
}