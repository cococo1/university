AL::ALMotionProxy motion(robotIp);
bool useSensors = true;
std::vector<float> currentWorldPosition = motion.getRobotPosition(useSensors);