#pragma once
#include <iostream>
#include "AudioEffect.h"

class DelayEffect : public AudioEffect {
private:
	std::vector<float> delayBuffer;
	int delayIndex = 0;

	//Parameters
	int delayMS = 500;
	float feedback = 0.3f;

public:
	DelayEffect(double sr, unsigned long bs);
	void process(float* input);
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};