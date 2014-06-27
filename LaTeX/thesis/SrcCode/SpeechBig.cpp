//
//  Speech.cpp
//  naoClusteringMac
//
//  Created by Maxim Chetrusca on 5/16/14.
//  Copyright (c) 2014 Maxim Chetrusca. All rights reserved.
//

#include "Speech.h"

//    Public methods:
void Speech:: say(std::string text)
{
    if (USE_SPEECH)
    {
#ifdef __linux__
    try
    {
        AL::ALTextToSpeechProxy tts(robotIp);
        /** Call the say method */
        //Change the language !!!

                tts.setLanguage("English");
                tts.say(text);
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "say not on linux: " << text << std::endl;
#endif
    }
    
}

std::string Speech:: recognizeSpeech()
{
    //    std::string recognizedSpeech;
#ifdef __linux__
    try
    {
        AL::ALSpeechRecognitionProxy speech(robotIp);
        speech.setLanguage("English");
        
        /// Setting the word list that should be recognized
        std::vector<std::string> wordlist;
        wordlist.push_back("Hi NAO!");
        wordlist.push_back("stop");
        wordlist.push_back("start");
        wordlist.push_back("cluster objects");
        wordlist.push_back("can you group some objects?");
        speech.setWordListAsVocabulary(wordlist);
        speech.subscribe("WordRecognized");
        speech.setVisualExpression(true);
        speech.setAudioExpression(true);
        
        AL::ALMemoryProxy memory(robotIp);
        
        while(true)
        {
            AL::ALValue data = memory.getData("WordRecognized");
            std::string words = data[0];
            //           strcpy(recognizedSpeech,words);
            //do some stuff...
            std::cout << words << std::endl;
            
            if (words.length() > 1)
            {
                say(words);
                speech.unsubscribe("WordRecognized");
                return words;
                
            }
            //
            //            if (1)
            //            {
            //                tts.say(words);
            //
            //                if (! words.compare("start"))
            //                {
            //                    //continue..
            //                }
            //
            //                break;
            //            }
            
            
            // do stuff...
        }
        
        
        
        
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "startSpeechRecognition not on linux " << std::endl;
#endif
    return "stop";
}

std::vector<float> Speech:: localizeSoundSource()
{
    std::vector<float> position;
#ifdef __linux__
    try
    {
        AL::ALAudioSourceLocalizationProxy audioSource(robotIp);
        audioSource.subscribe("SoundLocated");

        AL::ALMemoryProxy memory(robotIp);

        while(true)
        {
            AL::ALValue data = memory.getData("ALAudioSourceLocalization/SoundLocated");
            std::cout << data << std::endl;
            position = data[2];
            //           strcpy(recognizedSpeech,words);
            //do some stuff...
//            std::cout << words << std::endl;

            if (position.size() > 0)
            {
                audioSource.unsubscribe("SoundLocated");
                return position;
            }
        }
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "startSpeechRecognition not on linux " << std::endl;
#endif
    return position;
}


void Speech::startRecognition()
{
    
#ifdef __linux__
    try
    {
        AL::ALTextToSpeechProxy tts(robotIp);
        /** Call the say method */
        //Change the language !!!
        tts.setLanguage("English");
        
        //        AL::ALMemoryProxy memory(robotIp);
        AL::ALSpeechRecognitionProxy speech(robotIp);
        speech.setLanguage("English");
        
        /// Setting the word list that should be recognized
        std::vector<std::string> wordlist;
        wordlist.push_back("Hi NAO!");
        wordlist.push_back("start");
        speech.setWordListAsVocabulary(wordlist);
        speech.subscribe("WordRecognized");
        speech.setVisualExpression(true);
        speech.setAudioExpression(true);
        
        AL::ALMemoryProxy memory(robotIp);
        
        while(true)
        {
            AL::ALValue data = memory.getData("WordRecognized");
            std::string words = data[0];
            //do some stuff...
            std::cout << words << std::endl;
            
            
            if (1)
            {
                tts.say(words);
                
                if (! words.compare("start"))
                {
                    //continue..
                }
                
                break;
            }
            
            
            // do stuff...
        }
        speech.unsubscribe("WordRecognized");
        //        memory.subscribeToEvent("WordRecognized", "NAO",
        //        "onSpeechRecognized");
        //        memory.subscribe
        //        speech.subscribe("NAO");
        //        speech.callback()
        
        
        
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    //  /// Setting up a proxy to ALTextToSpeech
    //  fTextToSpeech = getParentBroker()->getProxy("ALTextToSpeech");
    //  /// Setting the language to "English"
    //  fTextToSpeech->callVoid("setLanguage",std::string("English"));
    
    //  /// Setting up a proxy to ALMemory
    //  fMemory = getParentBroker()->getMemoryProxy();
    
    //  /// Setting up a proxy to ALSpeechRecognition
    //  fSpeechRecognition = getParentBroker()->getProxy("ALSpeechRecognition");
    //  /// Setting the working language of speech recognition engine
    //  fSpeechRecognition->callVoid("setLanguage",std::string("English"));
    
    //  /// Setting the word list that should be recognized
    //  std::vector<std::string> wordlist;
    //  wordlist.push_back(fCommand);
    //  fSpeechRecognition->callVoid("setWordListAsVocabulary", wordlist);
    
    //  /// Launching the speech recognition engine by subscribing to a ALMemory
    //    key
    //  /// that is fed by ALSpeechRecognition. Note that a callback function
    //    is specified.
    //  fMemory->subscribeToEvent("WordRecognized",getName(),
    //    "onSpeechRecognized");
#else
    std::cout << "startSpeechRecognition not on linux " << std::endl;
#endif
}

void Speech:: stopRecognition()
{
#ifdef __linux__
    try
    {
        
        AL::ALSpeechRecognitionProxy speech(robotIp);
        //        speech.subscribe("WordRecognized");
        speech.unsubscribe("WordRecognized");
        //        AL::ALMemoryProxy memory(robotIp);
        //        memory.unsubscribeToEvent("WordRecognized", "NAO");
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
#else
    std::cout << "stopRecognition not on linux " << std::endl;
#endif
    //  /// Stopping the speech recognition engine by unsubscribing to the
    //    ALMemory key
    //    AL::ALSpeechRecognitionProxy speech(robotIp);
    //    speech.unsubscribe("NAO");
    ////  fMemory->unsubscribeToEvent("WordRecognized",getName());
}

/// This function is called by ALMemory every time the value of
/// the key "WordRecognized" is modified by the speech recognition engine.
#ifdef __linux__
void Speech:: onSpeechRecognized(const std::string& name,
                               const AL::ALValue& val,
                               const std::string& myName)
{
    try
    {
        /// Parse the list of words that has been recognized by
//        ALSpeechRecognition
        for(unsigned int i = 0; i < val.getSize()/2 ; ++i)
        {
            std::cout << "word recognized: " << val[i*2].toString() <<
            " with confidence: " << (float)val[i*2+1] << std::endl;
            
            /// If our "command" has been recognized, start a speech synthesis
//            reaction
            if((std::string)val[i*2] == "Ahoj" && (float)val[i*2+1] > 0.15)
            {
                say("Ahoj Max");
                //                fTextToSpeech->callVoid("say",
                //                std::string("Ahoj Max"));
            }
        }
    }
    catch (const AL::ALError& e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}
#endif




//Constructors:
Speech:: Speech(const std::string& robotIp):
robotIp(robotIp)
{
    
}
Speech:: Speech(const Speech& speech):
robotIp(speech.robotIp)
{
    
}
       
//Destructor:
Speech:: ~Speech()
{
    
}

//    Overloaded operators:
Speech& Speech:: operator=(const Speech& speech)
{
    if (this != &speech)
    {
        robotIp = speech.robotIp;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Speech& speech)
{
    stream << speech.robotIp << std::endl;
    return stream;
}
