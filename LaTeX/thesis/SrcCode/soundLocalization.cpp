std::vector<float> position;
AL::ALAudioSourceLocalizationProxy
audioSource(robotIp);
audioSource.subscribe("SoundLocated");

AL::ALMemoryProxy memory(robotIp);

while(true)
{
    AL::ALValue data = memory.getData("ALAudioSourceLocalization/SoundLocated");
    position = data[2];
    
    if (position.size() > 0)
    {
        audioSource.unsubscribe("SoundLocated");
        return position;
    }
}