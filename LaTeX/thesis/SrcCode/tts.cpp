//this constructor takes as a parameter a std::string with robot IP:
AL::ALTextToSpeechProxy tts(robotIp);
tts.setLanguage("English");
//text is some std::string:
tts.say(text);