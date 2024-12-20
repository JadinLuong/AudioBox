#pragma once
#include <iostream>
#include "AudioEffect.h"
#include "../utils/FrequencyWaves.h"

class HighPassFilterEffect : public AudioEffect {
private:
	float x1, x2, y1, y2, b0, b1, b2, a1, a2;

	//Parameters
	float freqCutOff;
	float QFactor;

public:
	HighPassFilterEffect(double sr, unsigned long bs);
	void process(float* input);
	void CalculateButterworthCoefficients();
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};
