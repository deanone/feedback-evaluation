
/* 
 * File:   Kmeans.h
 * Author: asal
 *
 * Created on February 17, 2017, 2:37 PM
 */

#ifndef KMEANS_H
#define KMEANS_H

#include "TravelProfile.h"
#include "Cluster.h"

class Kmeans
{
    /*! Number of clusters. */
    int k;		
    /* Maximum number of iterations for the convergence of the algorithm. */
    int numOfIterations;
    /*! The type of used distance metric. */
    bool noData;
        
public:
    /*! The data points (full dataset) to be clustered. */
    std::vector<TravelProfile> points;		
    /*! Initial clusters in data randomly chosen. */
    std::vector<Cluster*> initialClusters;
    /*! Current clusters. */
    std::vector<Cluster*> finalClusters;
    std::map<std::string, int> pointIDClusterIDAllocation;
    std::map<int, StringVector> clusterIDPointsOfClusterIDsAllocation;

public:
    /*! Constructor 1. */
    Kmeans(std::string datasetFilename, int numOfClusters, int numOfIt);
    /*! Constructor 2. */
    Kmeans(int numOfClusters, int numOfIt, std::string BASE_URL);
    
    /*! Destructor. */
    ~Kmeans();				

    /*! Sets the number of clusters. */
    void SetK(int k) {this->k = k;}
    /*! Gets the number of clusters. */
    int GetK() const {return k;}

    /*! Assigns Points to Clusters. */
    void SetPointsToClusters();
    /*! Creates the initial clusters by choosing k random Points from the dataset. */		
    void SetInitialClustersRandomly();
    /*! Creates the initial clusters by choosing the first k Points from the dataset. */
    void SetInitialClustersByInitialPoints();
    /*! Generates current clusters. */
    void SetFinalClusters();
    /*! Makes the final clusters of the iteration n-1 initial clusters for the iteration n. */	
    void Initialize();
    /*! Checks if the algorithm converged. */
    bool IsOver();
    /*! Runs the k-means routine. */
    void RunKmeans();
    void WriteCentroidsToFile(std::string centroidsFilename);
    void CreatePointIDClusterIDAllocation();
    void CreateClusterIDPointsOfClusterIDsAllocation();
    void WriteClusterIDPointsOfClusterIDsAllocationToFile(std::string allocationFilename1);
    void WritePointIDClusterIDAllocationToFile(std::string allocationFilename2);
    
    void CalculateClusterDistances(std::string distancesFilename);

    /*! Cluster validity metrics */

    /*! Calculates the Silhouette metric. */
    /*! https://en.wikipedia.org/wiki/Silhouette_(clustering) */
    //double calculateSilhouette();
    
	/*! Calculates Within Cluster Sum of Squares (WCSS). */
    double CalculateWCSS(); 

    /*!Davies-Bouldin index for clustering results internal evaluation. */
    /*! http://en.wikipedia.org/wiki/Cluster_analysis */
    /*! http://en.wikipedia.org/wiki/Davies%E2%80%93Bouldin_index */
    //double calculateDaviesBouldinIndex();
    
    bool GetNoData() const {return noData;}
    void SetNoData() {noData = true;}
    
    size_t GetNumOfPoints() {return points.size();}
    
};


#endif /* KMEANS_H */

