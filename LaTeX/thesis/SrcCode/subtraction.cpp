cv::Mat mask;
int history = 20;
int varThreshold = 50;
bool shadowDetection = true;
cv::Ptr<cv::BackgroundSubtractor> subtractor =
new cv::BackgroundSubtractorMOG2(history,
                                 varThreshold,
                                 shadowDetection);
subtractor->set("fVarInit", 100);
subtractor->set("fTau", 0);

subtractor->operator()(background.getMatrix(), mask);
subtractor->operator()(image.getMatrix(), mask);
subtractor.release();