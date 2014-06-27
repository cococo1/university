//
//  Camera.cpp
//  naoClustering
//
//  Created by Maxim Chetrusca on 2/14/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Camera.h"

#ifdef __linux__
    // Aldebaran includes.
    #include <alproxies/alvideodeviceproxy.h>
    #include <alvision/alimage.h>
//    #include <alvision/alvisiondefinitions.h>
    #include <alerror/alerror.h>
#endif
//#include "opencv2/opencv.hpp"

//Getters:
Image& Camera:: getImage()
{
    cv::Mat mat;
#ifdef __linux__
    static bool firstShot = true;

//       Create a proxy to ALVideoDevice on the robot.
    AL::ALVideoDeviceProxy camProxy(this->robotIp);
    
//       Subscribe a client image requiring 1280*960 and BGR colorspace.
//       kQQVGA
//       kQVGA
//       kVGA
//       k4VGA

    int fps = 30;
    const std::string clientName = camProxy.subscribeCamera("naoClustering",
                                                            AL::kBottomCamera,
                                                            AL::k4VGA,
                                                            AL::kBGRColorSpace,
                                                            fps);
    if (! clientName.compare("")) throw AL::ALError("Camera",
                                                    "getImage",
                                                    "Could not create \
                                                    camera proxy");

//       Create an cv::Mat header to wrap into an opencv image.
      cv::Mat imgHeader = cv::Mat(cv::Size(IMAGE_WIDTH, IMAGE_HEIGHT), CV_8UC3);

//         Retrieve an image from the camera.
//         The image is returned in the form of a container object, with the
//         following fields:
//         0 = width
//         1 = height
//         2 = number of layers
//         3 = colors space index (see alvisiondefinitions.h)
//         4 = time stamp (seconds)
//         5 = time stamp (micro seconds)
//         6 = image buffer (size of width * height * number of layers)
    
        AL::ALValue img = camProxy.getImageRemote(clientName);

//         Access the image buffer (6th field) and assign it to the opencv image
//         container.
        imgHeader.data = (uchar*) img[6].GetBinary();
        imgHeader.copyTo(mat);

//        Tells to ALVideoDevice that it can give back the image buffer to the
//         driver. Optional after a getImageRemote but MANDATORY after a
//    getImageLocal.
        camProxy.releaseImage(clientName);

//       Cleanup.
      camProxy.unsubscribe(clientName);
#endif
    return *new Image(mat);

}

//Constructors:
Camera:: Camera(const std::string& robotIp):
    robotIp(robotIp),
AbstractImageFetcher()
{
    
}

Camera:: Camera(const Camera& camera):
    robotIp(camera.robotIp),
AbstractImageFetcher(camera)
{
    
}

//Destructor:
Camera:: ~Camera()
{
    
}

//Overloaded operators:
Camera& Camera:: operator=(const Camera& camera)
{
    if (this != & camera)
    {
        this->AbstractImageFetcher::operator=(camera);
        robotIp = camera.robotIp;
        
    }
    
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Camera& camera)
{
    stream << (AbstractImageFetcher&)camera << " " << camera.robotIp
    << std::endl;
    
    return stream;
}


