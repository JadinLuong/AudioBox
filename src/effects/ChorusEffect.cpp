#include <iostream>
#include <iomanip>
#include "ChorusEffect.h"

ChorusEffect::ChorusEffect(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;
	effectName = "Chorus";
	effectAlias = "chorus-effect";
	effectDescription = "Chorus Effect adds a modulated version of the audio with itself.";

	delayMS = 30.0f;
	lfoDepth = 10.0f;
	maxDelaySamples = sampleRate * delayMS / 1000;
	delayBuffer.resize(maxDelaySamples, 0.0f);
	delayIndex = 0;

	fw = FrequencyWaves(sampleRate, bufferSize);
	fw.setFreq(2);
	fw.setAmp(1);

	mix = 0.3f;
	effectStatus = false;
}

void ChorusEffect::process(float* input) {
	std::vector<float> LFO = fw.generateSinWave();
	for (unsigned long i = 0; i < bufferSize; i++) {
		float dry = input[i];

		float modDelayMS = lfoDepth * LFO[i];
		int delaySamples = static_cast<int>(sampleRate * modDelayMS / 1000.0f);
		int readIndex = (delayIndex - delaySamples + maxDelaySamples) % maxDelaySamples;

		int prevIndex = (readIndex - 1 + maxDelaySamples) % maxDelaySamples;
		float frac = readIndex - std::floor(readIndex);
		float wet = (1.0f - frac) * delayBuffer[readIndex] + frac * delayBuffer[prevIndex];

		input[i] = (1.0f - mix) * input[i] + mix * wet;

		delayBuffer[delayIndex] = dry;
		delayIndex = (delayIndex + 1) % maxDelaySamples;
	}
}

void ChorusEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "delay") {
		delayMS = value;
		changeParameterLog("Delay", value);
	}
	else if (parameter == "depth") {
		lfoDepth = value;
		changeParameterLog("Depth", value);
	}
	else if (parameter == "mix") {
		mix = value;
		changeParameterLog("Mix", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void ChorusEffect::getParameterInfo() {
	std::cout << "Delay: " << delayMS << std::endl;
	std::cout << "Depth: " << lfoDepth << std::endl;
	std::cout << "Mix: " << mix << std::endl;
}