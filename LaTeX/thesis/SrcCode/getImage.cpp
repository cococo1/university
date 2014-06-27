AL::ALVideoDeviceProxy camProxy(this->robotIp);
int fps = 30;
const std::string clientName = camProxy.subscribeCamera("naoClustering",
                                                        AL::kBottomCamera,
                                                        AL::k4VGA,
                                                        AL::kBGRColorSpace,
                                                        fps);
AL::ALValue img = camProxy.getImageRemote(clientName);