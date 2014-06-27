cv::Mat labels;
cv::TermCriteria criteria =
cv::TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,
                 10,
                 1.0);
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