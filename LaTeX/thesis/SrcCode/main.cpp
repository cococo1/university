#include <iostream>
#include <exception>
#include "NAO.h"
#ifdef __linux__
    #include <alerror/alerror.h>
    #include <alproxies/altexttospeechproxy.h>
    #include <alproxies/almotionproxy.h>
    #include <alproxies/alrobotpostureproxy.h>
    #include <alproxies/alnavigationproxy.h>
#else
    #include <unistd.h>
#endif

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cerr << "Wrong number of arguments!" << std::endl;
    std::cerr << "Usage: naoClustering NAO_IP" << std::endl;
    exit(EXIT_FAILURE);
  }
    try
    {
        std::string robotIp = argv[1];
        
        AbstractFactory *factory = new AbstractFactory();
        NAO fitik(robotIp, factory);

        fitik.startInteraction();
}
catch (std::exception& e)
{
    std::cerr << "Exceptionale: " << e.what() << std::endl;
}
    exit(EXIT_SUCCESS);
}