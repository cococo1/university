//
//  KMeansClusteringAlgorithm.h
//  naoClustering
//
//  Created by Maxim Chetrusca on 4/21/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClustering__KMeansClusteringAlgorithm__
#define __naoClustering__KMeansClusteringAlgorithm__

//#include <iostream>
//#include <vector>
#include "AbstractClusterAlgorithm.h"
const unsigned SQUARE_SIZE = 0;
const unsigned NUMBER_OF_FEATURES = 7;
const unsigned NUMBER_OF_ITERATIONS_PER_ONE_RUN = 10;
const unsigned NUMBER_OF_RANDOM_INITIALIZATIONS = 40;

//This class implements K-means clustering algorithm;
//It uses OpenCV built-in algorithm + customly implemented "Elbow method"
// in order to determine the number of clusters.
class KMeansClusteringAlgorithm: public AbstractClusterAlgorithm
{
public:
//    Public methods:
//    This method does the whole job:
//    after its call, object.group would be assigned
//    here we also define the abstract method from the superclass:
    virtual unsigned assignGroupsToObjects(std::vector<Object>& objects);
    
//Constructors:
    KMeansClusteringAlgorithm();
    KMeansClusteringAlgorithm(const KMeansClusteringAlgorithm& algorithm);
    
//Destructor:
    virtual ~KMeansClusteringAlgorithm();
    
//    Overloaded operators:
    KMeansClusteringAlgorithm& operator=(
     const KMeansClusteringAlgorithm& algorithm);
    friend std::ostream& operator<<(std::ostream& stream,
                                    const KMeansClusteringAlgorithm& algorithm);
    
//    Private methods:
private:
    //returns a matrix of floats containing NUMBER_OF_EXAMPLES rows, each
//    with NUMBER_OF_FEATURES columns, filled with scaled and normalized data.
    float** assignFeaturesFromObjects(std::vector<Object>& objects);
    //returns a matrix of K centroids, each with NUMBER_OF_FEATURES features:
    float** initializeCentroidsGivenTrainingSet(float** trainingSet,
                                                unsigned n,
                                                unsigned K);
    //Compute the Euclidean distance from centroid to point, and assign
    //this point to the closest centroid:
    void assignClusters(int* clusters,
                        float** trainingSet,
                        float** centroids,
                        unsigned n,
                        unsigned K);
//    Given the previous assignment of clusters, determine where is the
//    geometric center of a cluster:
    void moveCentroids(int* clusters,
                       float** trainingSet,
                       float** centroids,
                       unsigned n,
                       unsigned K);
//    clustering is an iterative process: assign centroids, and move them:
    int* cluster(float** trainingSet,
                 float** centroids,
                 unsigned n,
                 unsigned K);
//    as we try to find optimal number of clusters, we need to compute the error
//    for each case:
    float computeError(int* clusters,
                       float** trainingSet,
                       float** centroids,
                       unsigned n,
                       unsigned K);
    //Only a few of the above functions are used with this method; others are
    //for custom implementation.
    unsigned kMeansClusteringOpenCVImplementation(std::vector<Object>& objects,
                                                  float** trainingSet,
                                                  int numberOfTrainingExamples);
    unsigned kMeansClusteringCustomImplementation(std::vector<Object>& objects,
                                                  float** trainingSet,
                                                  int numberOfTrainingExamples);

    
};

#endif /* defined(__naoClustering__KMeansClusteringAlgorithm__) */
