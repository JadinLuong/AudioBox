#pragma once
#include <iostream>
#include <vector>
#include <cmath>

class FrequencyWaves {
private:
	double PI = 3.141592654;

	double sampleRate;
	unsigned long bufferSize;

	double freq = 440;
	double amp = 1;

	double currentPhase = 0.0;
	double lfoPhase = 0.0;

	double modDepth = 0.0; // if moddepth == 0 then no modulation is going to occur
	double modFreq = 0.0; // modifies speed of wave


public:

	FrequencyWaves(double sr = 44100, unsigned long bs = 256);

	std::vector<float> generateSinWave();

	std::vector<float> generateTriangleWave();

	std::vector<float> generateSawToothWave();

	std::vector<float> generateSquareWave();

	double getFreq();

	void setFreq(double f);

	double getAmp();

	void setAmp(double a);

};