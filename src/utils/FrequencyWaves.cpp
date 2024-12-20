#include <iostream>
#include <vector>
#include <cmath>
#include "FrequencyWaves.h"

FrequencyWaves::FrequencyWaves(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;
}

std::vector<float> FrequencyWaves::generateSinWave() {
	double lfoPhaseIncrement = 2 * PI * modFreq / sampleRate;
	double modulatedFreq = freq + modDepth * sin(lfoPhase);
	double phaseIncrement = 2 * PI * modulatedFreq / sampleRate;

	std::vector<float> output(bufferSize);

	for (unsigned long i = 0;i < bufferSize;i++) {
		output[i] = amp * sin(currentPhase);

		currentPhase += phaseIncrement;
		lfoPhase += lfoPhaseIncrement;

		if (currentPhase >= 2 * PI) {
			currentPhase = 0;
		}
		if (lfoPhase >= 2 * PI) {
			lfoPhase = 0;
		}
	}

	return output;
}

std::vector<float> FrequencyWaves::generateTriangleWave() {
	double lfoPhaseIncrement = 2 * PI * modFreq / sampleRate;
	double modulatedFreq = freq + modDepth * sin(lfoPhase);
	double phaseIncrement = 2 * PI * modulatedFreq / sampleRate;

	std::vector<float> output(bufferSize);

	for (unsigned long i = 0;i < bufferSize;i++) {
		output[i] = amp * (2/PI) * asin(sin(currentPhase));

		currentPhase += phaseIncrement;
		lfoPhase += lfoPhaseIncrement;

		if (currentPhase >= 2 * PI) {
			currentPhase = 0;
		}
		if (lfoPhase >= 2 * PI) {
			lfoPhase = 0;
		}
	}

	return output;
}

std::vector<float> FrequencyWaves::generateSawToothWave() {
	double lfoPhaseIncrement = 2 * PI * modFreq / sampleRate;
	double modulatedFreq = freq + modDepth * sin(lfoPhase);
	double phaseIncrement = modulatedFreq / sampleRate;

	std::vector<float> output(bufferSize);

	for (unsigned long i = 0;i < bufferSize;i++) {
		output[i] = amp * (currentPhase - floor(currentPhase));

		currentPhase += phaseIncrement;
		lfoPhase += lfoPhaseIncrement;

		if (currentPhase >= 1.0) {
			currentPhase = 0;
		}
		if (lfoPhase >= 2 * PI) {
			lfoPhase = 0;
		}
	}

	return output;
}

std::vector<float> FrequencyWaves::generateSquareWave() {
	double lfoPhaseIncrement = 2 * PI * modFreq / sampleRate;
	double modulatedFreq = freq + modDepth * sin(lfoPhase);
	double phaseIncrement = modulatedFreq / sampleRate;

	std::vector<float> output(bufferSize);

	for (unsigned long i = 0; i < bufferSize; i++) {
		if (currentPhase < 0.5) {
			output[i] = amp;
		}
		else {
			output[i] = -amp;
		}

		currentPhase += phaseIncrement;
		lfoPhase += lfoPhaseIncrement;

		if (currentPhase >= 1.0) {
			currentPhase = 0.0;
		}
		if (lfoPhase >= 2 * PI) {
			lfoPhase = 0;
		}
	}

	return output;
}

double FrequencyWaves::getFreq() {
	return freq;
}

void FrequencyWaves::setFreq(double f) {
	this->freq = f;
}

double FrequencyWaves::getAmp() {
	return amp;
}

void FrequencyWaves::setAmp(double a) {
	this->amp = a;
}