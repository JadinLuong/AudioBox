#include <iostream>
#include <vector>
#include "../utils/FrequencyWaves.h"
#include "RingModEffect.h"

RingModEffect::RingModEffect(double sr, unsigned long bs) {
	frequencyWaves = FrequencyWaves(sr, bs);
	sampleRate = sr;
	bufferSize = bs;
	effectName = "Ring Modulation";
	effectAlias = "ring-mod-effect";
	effectDescription = "Ring Modulation Effect combines the audio signal with a modulated signal.";

	effectStatus = false;
	waveSelection = SIN_WAVE;
}

void RingModEffect::process(float* input) {
	std::vector<float> carrierSignal;

	switch (waveSelection) {
	case SIN_WAVE:
		carrierSignal = frequencyWaves.generateSinWave();
		break;
	case SAWTOOTH_WAVE:
		carrierSignal = frequencyWaves.generateSawToothWave();
		break;
	case TRIANGLE_WAVE:
		carrierSignal = frequencyWaves.generateTriangleWave();
		break;
	case SQUARE_WAVE:
		carrierSignal = frequencyWaves.generateSquareWave();
		break;
	default:
		carrierSignal = frequencyWaves.generateSinWave();
		break;
	}

	for (unsigned long i = 0; i < bufferSize; i++) {
		input[i] = input[i] * carrierSignal[i];
	}
}

void RingModEffect::changeCarrierSignal(int signal) {
	waveSelection = signal;
}

void RingModEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "frequency-wave") {
		waveSelection = value;
		changeParameterLog("Frequency Wave", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void RingModEffect::getParameterInfo() {
	std::cout << "Frequency Wave: " << waveSelection << std::endl;
}