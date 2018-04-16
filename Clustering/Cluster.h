/* 
 * File:   Cluster.h
 * Author: asal
 *
 * Created on February 17, 2017, 2:31 PM
 */

#ifndef CLUSTER_H
#define CLUSTER_H

#include "TravelProfile.h"

class Cluster
{
    /*! ID of the cluster. */
    int ID; 
     
public:
    /*! Center of the cluster. */
    TravelProfile center; 
    
    /*! Points of the cluster. */
    std::vector<TravelProfile*> pointsOfCluster;
    
    /*! Constructor. */
    Cluster(int id);
    
    /*! Destructor. */
    ~Cluster();

    /*! Sets the ID of the cluster. */
    void SetID(int ID) {this->ID = ID;}		
    /*! Returns the ID of the cluster. */
    int GetID() {return ID;}

    /*! Adds point to the set of the points consisting the cluster. */
   //void setPointsToCluster(TravelProfile *p);
    /*! Returns the number of points in this cluster. */
    //int getNumOfPointsInCluster();
    /*! Returns a point of the cluster for the specific index. */
    //TravelProfile* getPointOfCluster(int index);
    /*! Delete points of cluster. */
    //void clearPointsOfCluster();

    /*! Overloaded operators functions. */
    bool operator==(Cluster &c);

    /*! Prints the centroid of the cluster to console. */
    void PrintCentroidInConsole();
    /*! Prints the ids of the points of cluster to console. */
    void PrintAllocationInConsole();
    /*! Writes the centroid of the cluster to file. */
    void WriteCentroidToFile(std::ostream &out);
    /*! Writes the ids of the points of cluster to file */
    void WriteAllocationToFile(std::ostream &out);
};

#endif /* CLUSTER_H */

