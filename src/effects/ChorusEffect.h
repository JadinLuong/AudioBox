#pragma once
#include <iostream>
#include "AudioEffect.h"
#include "../utils/FrequencyWaves.h"

class ChorusEffect : public AudioEffect {
private:
	FrequencyWaves fw;
	std::vector<float> delayBuffer;
	int delayIndex;
	int maxDelaySamples;

	// Parameters
	float delayMS;
	float lfoDepth;
	float mix;
public:
	ChorusEffect(double sr, unsigned long bs);
	void process(float* input);
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};