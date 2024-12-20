#pragma once
#include <iostream>
#include <vector>
#include "AudioEffect.h"
#include "../utils/FrequencyWaves.h"

const int SIN_WAVE = 1;
const int SAWTOOTH_WAVE = 2;
const int TRIANGLE_WAVE = 3;
const int SQUARE_WAVE = 4;

class RingModEffect : public AudioEffect {
private:
	FrequencyWaves frequencyWaves;

	//Parameters
	int waveSelection;
public:
	RingModEffect(double sr = 44100, unsigned long bs = 256);
	void process(float* input) override;
	void changeCarrierSignal(int signal);
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};
