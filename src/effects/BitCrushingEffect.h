#pragma once
#include <iostream>
#include "AudioEffect.h"
#include "../utils/FrequencyWaves.h"

class BitCrushingEffect : public AudioEffect {
private:
	float bitDepth = 4;
public:
	BitCrushingEffect(double sr, unsigned long bs);
	void process(float* input);
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};
