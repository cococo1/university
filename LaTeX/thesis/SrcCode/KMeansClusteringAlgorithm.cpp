//
//  KMeansClusteringAlgorithm.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 4/21/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "KMeansClusteringAlgorithm.h"
#include <set>
#include <stdlib.h>
#include <time.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//Here are the features taken into consideration by clustering algorithm:
//    //Features:
//    //matrix.cols;
//    //matrix.rows;
//    //mean(matrix)[0];
//    //mean(matrix)[1];
//    //mean(matrix)[2];
//abs(matrix.cols - matrix.rows);
//matrix.cols*matrix.cols;

//Public methods:
unsigned KMeansClusteringAlgorithm:: assignGroupsToObjects(
   std::vector<Object>& objects)
{
    unsigned numberOfTrainingExamples = (unsigned)objects.size();
//    create the training set; extract the features:
    float** trainingSet = assignFeaturesFromObjects(objects);
//    perform the clustering:
    return kMeansClusteringOpenCVImplementation(objects,
                                                trainingSet,
                                                numberOfTrainingExamples);
}

//Constructors:
KMeansClusteringAlgorithm:: KMeansClusteringAlgorithm():
AbstractClusterAlgorithm()
{
    
}

KMeansClusteringAlgorithm:: KMeansClusteringAlgorithm(
                              const KMeansClusteringAlgorithm& algorithm):
AbstractClusterAlgorithm(algorithm)
{
    
}

//Destructor:
KMeansClusteringAlgorithm:: ~KMeansClusteringAlgorithm()
{
    
}

//Overloaded operators:
KMeansClusteringAlgorithm& KMeansClusteringAlgorithm:: operator=(
                             const KMeansClusteringAlgorithm& algorithm)
{
    if (this != &algorithm)
    {
        AbstractClusterAlgorithm::operator=(algorithm);
    }
    
    return *this;
    
}

std::ostream& operator<<(std::ostream& stream,
                         const KMeansClusteringAlgorithm& algorithm)
{
    stream << *((AbstractClusterAlgorithm*)&algorithm);
    return stream;
}

//Private methods:
float** KMeansClusteringAlgorithm:: assignFeaturesFromObjects(
      std::vector<Object>& objects)
{
    unsigned numberOfTrainingExamples = (unsigned)objects.size();
    //Allocate memory:
    float** trainingSet = new float*[numberOfTrainingExamples];
    for (int i = 0; i < numberOfTrainingExamples; i++)
    {
        trainingSet[i] = new float[NUMBER_OF_FEATURES];
    }
    
    //For normalization and feature scaling:
    float maxFeatureValue[NUMBER_OF_FEATURES];
    float avgFeatureValue[NUMBER_OF_FEATURES];
    for (int i = 0; i < NUMBER_OF_FEATURES; i++)
    {
        maxFeatureValue[i] = 0;
        avgFeatureValue[i] = 0;
    }
    
    
    //Extract features:
    int j = 0;
    for(std::vector<Object>::iterator it = objects.begin();
        it != objects.end();
        ++it)
    {
        Object object = *it;
        Image image = object.getImage();
        cv::Mat matrix = image.getMatrix();
        cv::Scalar m = mean(matrix);
        
        trainingSet[j][0] = matrix.cols; //width
        trainingSet[j][1] = matrix.rows; //height
        trainingSet[j][2] = m[0]; //avg Blue
        trainingSet[j][3] = m[1]; //avg Green
        trainingSet[j][4] = m[2]; //avg Red
        //how "square" is the image:
        trainingSet[j][5] = abs(matrix.cols - matrix.rows);
        trainingSet[j][6] = matrix.cols*matrix.cols; //how big is the image
        
        //Find max and avg feature values:
        for (int k = 0; k < NUMBER_OF_FEATURES; k++)
        {
            if (maxFeatureValue[k] < trainingSet[j][k])
            {
                maxFeatureValue[k] = trainingSet[j][k];
            }
            avgFeatureValue[k] += trainingSet[j][k];
        }
        
        j++;
    }
    
    //Compute the avg:
    for (int k = 0; k < NUMBER_OF_FEATURES; k++)
    {
        avgFeatureValue[k] /= objects.size();
    }
    //Normalize features using max and avg feature values:
    j = 0;
    for(std::vector<Object>::iterator it = objects.begin();
        it != objects.end();
        ++it)
    {
        for (int i = 0; i < NUMBER_OF_FEATURES; i++)
        {
            trainingSet[j][i] = (trainingSet[j][i] - avgFeatureValue[i]) /
            maxFeatureValue[i];
            
            //This should not happen:
            if ((trainingSet[j][i] < -1) || (trainingSet[j][i] > 1))
            {
                std::cout << trainingSet[j][i] << " ";
            }
            
        }
        
        j++;
    }
    
    return trainingSet;
}

float** KMeansClusteringAlgorithm:: initializeCentroidsGivenTrainingSet(
    float** trainingSet, unsigned n, unsigned K)
{
//    Allocate memory:
    float** centroids = new float*[K];
    for (int i = 0; i < K; i++)
    {
        centroids[i] = new float[NUMBER_OF_FEATURES];
    }
    
//    Random initialization of centroids;
//    need to keep track with points were already chosen as centroids
//    so that we do not choose the same point twice:
    std::set<int> previousCentroids;
    for (int i = 0; i < K; i++)
    {
        unsigned rnd;
//         initialize random seed: 
        srand ((unsigned)time(NULL));
    
        while (previousCentroids.find(rnd = rand() % n) !=
               previousCentroids.end());
        previousCentroids.insert(rnd);
        
        for (int j = 0; j < NUMBER_OF_FEATURES; j++)
        {
            centroids[i][j] = trainingSet[rnd][j];
        }
    }
    return centroids;
}

void KMeansClusteringAlgorithm:: assignClusters(int* clusters,
                                                float** trainingSet,
                                                float** centroids,
                                                unsigned n,
                                                unsigned K)
{
    for (int i = 0; i < n; i++)
    {
        float minimalDistance = -1;
        unsigned centroid = 1;
        
        for (int k = 0; k < K; k++)
        {
            //Get vector:
            std::vector<float> v;
            for (int l = 0; l < NUMBER_OF_FEATURES; l++)
            {
                v.push_back(trainingSet[i][l] - centroids[k][l]);
            }
            float someDistance = cv::norm(v);
            someDistance *= someDistance;
            if (minimalDistance < 0)
            {
                minimalDistance = someDistance;
                centroid = k;
            }
            if (minimalDistance > someDistance)
            {
                minimalDistance = someDistance;
                centroid = k;
            }
        }
        
        clusters[i] = centroid;
    }
}

void KMeansClusteringAlgorithm:: moveCentroids(int* clusters,
                                               float** trainingSet,
                                               float** centroids,
                                               unsigned n,
                                               unsigned K)
{
    for (int k = 0; k < K; k++)
    {
        int numberOfAssignedObjects = 0;
        for (int l = 0; l < NUMBER_OF_FEATURES; l++)
        {
            centroids[k][l] = 0;
        }
        
        for (int i = 0; i < n; i++)
        {
            if (clusters[i] == k)
            {
                numberOfAssignedObjects++;
                for (int l = 0; l < NUMBER_OF_FEATURES; l++)
                {
                    centroids[k][l] += trainingSet[i][l];
                }
                
            }
        }
        
        for (int l = 0; l < NUMBER_OF_FEATURES; l++)
        {
            centroids[k][l] /= numberOfAssignedObjects;
        }
    }
}

int* KMeansClusteringAlgorithm:: cluster(float** trainingSet,
                                         float** centroids,
                                         unsigned n,
                                         unsigned K)
{
    int *clusters = new int[n];
    for (int iterations = 0;
         iterations < NUMBER_OF_ITERATIONS_PER_ONE_RUN;
         iterations++)
    {
        assignClusters(clusters, trainingSet, centroids, n, K);
        moveCentroids(clusters, trainingSet, centroids, n, K);

        if (K == 1)
        {
            break;
        }
    }
    return clusters;
}

float KMeansClusteringAlgorithm:: computeError(int* clusters,
                                               float** trainingSet,
                                               float** centroids,
                                               unsigned n,
                                               unsigned K)
{
    float error = 0;
    
    for (int i = 0 ; i < n; i++)
    {
        for (int j = 0; j < K; j++)
        {
            if (clusters[i] == j)
            {
                std::vector<float> v;
                for (int l = 0; l < NUMBER_OF_FEATURES; l++)
                {
                    float a = trainingSet[i][l] - centroids[j][l];
                    
                    v.push_back(a);
                }
                error += cv::norm(v);
            }
        }
    }
    error /= n;
    
    return error;
}

unsigned KMeansClusteringAlgorithm:: kMeansClusteringOpenCVImplementation(
std::vector<Object>& objects, float** trainingSet, int numberOfTrainingExamples)
{
    int* bestLabeling = new int[numberOfTrainingExamples];
    float previousError = -1;
    float previousErrorRatio = 1;
    int resultingNumberOfClusters = 1;
    
    cv::Mat data(numberOfTrainingExamples, NUMBER_OF_FEATURES, CV_32FC1);
    for (int i = 0; i < numberOfTrainingExamples; i++)
    {
        for (int j = 0; j < NUMBER_OF_FEATURES; j++)
        {
            data.at<float>(i,j) = trainingSet[i][j];
        }
    }

    for (int numberOfClusters = 1;
         numberOfClusters <= numberOfTrainingExamples;
         numberOfClusters++)
    {
        cv::Mat labels;
        cv::TermCriteria criteria =
        cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0);
        int attempts = NUMBER_OF_ITERATIONS_PER_ONE_RUN;
        int flags = cv::KMEANS_PP_CENTERS ;
        cv::Mat centers(numberOfClusters, 1, data.type());
        
        cv::kmeans(data,
                   numberOfClusters,
                   labels,
                   criteria,
                   attempts,
                   flags,
                   centers);
        if (numberOfTrainingExamples == 1)
        {
            //Strange enough, when there is just one object,
//            the group assigned to it is 8;
            //Let's correct that:
            labels.at<int>(0) = 0;
        }


        int* clusters = new int[numberOfTrainingExamples];
        
        for (int i = 0; i < numberOfTrainingExamples; i++)
        {
            clusters[i] = labels.at<int>(i);
        }
        
        float** centroids = new float*[numberOfClusters];
        for (int i = 0; i < numberOfClusters; i++)
        {
            centroids[i] = new float[NUMBER_OF_FEATURES];
            for (int j = 0; j < NUMBER_OF_FEATURES; j++)
            {
                centroids[i][j] = centers.at<float>(i,j);
            }
        }
        
        float error = computeError(clusters,
                                   trainingSet,
                                   centroids,
                                   numberOfTrainingExamples,
                                   numberOfClusters);
        
        for (int i = 0; i < numberOfClusters; i++)
        {
            delete []centroids[i];
        }
        delete []centroids;
        delete []clusters;

        if (error == 0)
        {
                        resultingNumberOfClusters = numberOfClusters;
                        for (int i = 0; i < numberOfTrainingExamples; i++)
                        {
                            bestLabeling[i] = labels.at<int>(i);
                        }

                        break;
        }

        if (previousError < 0) previousError = error;
//        std::cout <<"Number of clusters: " <<numberOfClusters <<" Error: " <<
//        error << std::endl;
//        std::cout << previousError/error << std::endl;
        if (previousErrorRatio > previousError/error)
        {
            break;
        }
        else
        {
            resultingNumberOfClusters = numberOfClusters;
            previousErrorRatio = previousError/error;
            for (int i = 0; i < numberOfTrainingExamples; i++)
            {
                bestLabeling[i] = labels.at<int>(i);
            }
        }
        previousError = error;
    }
    
//Cleanup:
    for (int i = 0; i < numberOfTrainingExamples; i++)
    {
        delete []trainingSet[i];
    }
    delete []trainingSet;
    
//    Label the objects:
    int i = 0;
    for(std::vector<Object>::iterator it = objects.begin();
        it != objects.end();
        ++it)
    {
        (*it).setGroup(bestLabeling[i]);

        std::cout << i << " " << bestLabeling[i] << std::endl;
        i++;
        
    }
    delete []bestLabeling;
    
    return resultingNumberOfClusters;
}

unsigned KMeansClusteringAlgorithm:: kMeansClusteringCustomImplementation(
std::vector<Object>& objects, float** trainingSet, int numberOfTrainingExamples)
{
    int* bestBestClustering = new int[numberOfTrainingExamples];
    float previousError = 0;
    float previousErrorRatio = 1;
    int resultingNumberOfClusters = 0;
    for (int numberOfClusters = 1;
         numberOfClusters <= numberOfTrainingExamples;
         numberOfClusters++)
    {
        float minimalError = 1000000000;
        int* bestClustering = new int[numberOfTrainingExamples];
        
        for (int j = 0; j < NUMBER_OF_RANDOM_INITIALIZATIONS; j++ )
        {
            float** centroids = initializeCentroidsGivenTrainingSet(trainingSet,
                                                    numberOfTrainingExamples,
                                                            numberOfClusters);
            
            int* clusters = cluster(trainingSet,
                                    centroids,
                                    numberOfTrainingExamples,
                                    numberOfClusters);
            
            float error = computeError(clusters,
                                       trainingSet,
                                       centroids,
                                       numberOfTrainingExamples,
                                       numberOfClusters);
            
            if (error < minimalError)
            {
                minimalError = error;
                for (int i = 0; i < numberOfTrainingExamples; i++)
                {
                    bestClustering[i] = clusters[i];
                }
            }

            for (int i = 0; i < numberOfClusters; i++)
            {
                delete []centroids[i];
            }
            delete []centroids;
            
            delete []clusters;
        }
        if (! previousError) previousError = minimalError;
        
        if (previousErrorRatio > previousError/minimalError)
        {
            break;
        }
        else
        {
            resultingNumberOfClusters = numberOfClusters;
            previousErrorRatio = previousError/minimalError;
            for (int i = 0; i < numberOfTrainingExamples; i++)
            {
                bestBestClustering[i] = bestClustering[i];
            }
        }
        delete []bestClustering;
        previousError = minimalError;
    }
    
    for (int i = 0; i < numberOfTrainingExamples; i++)
    {
        delete []trainingSet[i];
    }
    delete []trainingSet;
    
    int i = 0;
    for(std::vector<Object>::iterator it = objects.begin();
        it != objects.end();
        ++it)
    {
        (*it).setGroup(bestBestClustering[i]);
        i++;
    }
    delete []bestBestClustering;
    
    return resultingNumberOfClusters;
}





