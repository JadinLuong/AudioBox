#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <portaudio.h>
#include "../effects/AudioEffect.h"
#include "../utils/Logger.h"

class AudioProcessor {

private:

	double sampleRate;
	unsigned long bufferSize;
	std::map<std::string, AudioEffect*> audioEffects;
	std::vector<AudioEffect*> processingChain;
	

public:
	AudioProcessor();
	AudioProcessor(double sr, unsigned long bs);
	~AudioProcessor();
	void changeParameter(std::string effectName, std::string parameter, float value);
	void applyEffects(float* input);
	void toggleEffect(std::string effectName);
	void initializeEffects();
	std::map<std::string, AudioEffect*>& getAudioEffects();
};