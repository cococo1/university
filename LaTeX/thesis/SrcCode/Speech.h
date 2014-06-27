//
//  Speech.h
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#ifndef __naoClusteringMac__Voice__
#define __naoClusteringMac__Voice__

#include <iostream>

#ifdef __linux__
    #include <alerror/alerror.h>
    #include <alproxies/altexttospeechproxy.h>
    #include <alproxies/almemoryproxy.h>
    #include <alproxies/alspeechrecognitionproxy.h>
    #include <alproxies/alaudiosourcelocalizationproxy.h>
#else
    #ifdef __APPLE__
        #include <vector>
    #endif
#endif

const int USE_SPEECH = 1;

//This class incorporates the functionality of both
//Text-to-Speech and voice recognition
class Speech
{
    
//    Public methods:
public:
    void say(std::string text);
    std::string recognizeSpeech();
    std::vector<float> localizeSoundSource();


    void startRecognition();
    void stopRecognition();
#ifdef __linux__
    void onSpeechRecognized(const std::string& name,
                            const AL::ALValue& val,
                            const std::string& myName);
#endif



    //Constructors:
    Speech(const std::string& robotIp);
    Speech(const Speech& speech);
    
    //Destructor:
    virtual ~Speech();
    
    //    Overloaded operators:
    Speech& operator=(const Speech& speech);
    friend std::ostream& operator<<(std::ostream& stream, const Speech& speech);
    
private:
    std::string robotIp;
};

#endif /* defined(__naoClusteringMac__Voice__) */
