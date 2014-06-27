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
//this starts the recognition:
speech.subscribe("WordRecognized");
//some feedback by robot when he recognizes speech:
speech.setVisualExpression(true);
speech.setAudioExpression(true);