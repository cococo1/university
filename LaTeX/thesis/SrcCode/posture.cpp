AL::ALRobotPostureProxy robotPosture(robotIp);
float maxSpeedFraction = 0.5f; //[0;1]
bool postureReached = robotPosture.goToPosture("Stand", maxSpeedFraction);