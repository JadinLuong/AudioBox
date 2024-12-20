#include <iostream>
#include "HighPassFilterEffect.h"

HighPassFilterEffect::HighPassFilterEffect(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;

	effectName = "High Pass Filter";
	effectAlias = "hpf-effect";
	effectDescription = "High Pass Filter Effect removes LOWER frequencies at a specified cutoff from the audio signal.";

	freqCutOff = 3000.0f;
	QFactor = 2.0f;

	CalculateButterworthCoefficients();

	effectStatus = false;
}

void HighPassFilterEffect::process(float* input) {

	for (unsigned long i = 0; i < bufferSize; i++) {
		float x = input[i];

		float y = b0 * x + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2;

		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;

		input[i] = y;
	}
}

void HighPassFilterEffect::CalculateButterworthCoefficients() {
	float omega_c = 2.0f * 3.141 * freqCutOff / sampleRate;
	float alpha = sin(omega_c) / QFactor;

	float cos_omega_c = cos(omega_c);

	x1 = 0.0f;
	x2 = 0.0f;
	y1 = 0.0f;
	y2 = 0.0f;

	float a0 = 1.0f + alpha;
	b0 = (1.0f + cos_omega_c) / 2.0f / a0;
	b1 = -(1.0f + cos_omega_c) / a0;
	b2 = (1.0f + cos_omega_c) / 2.0f / a0;
	a1 = -(2.0f * cos_omega_c) / a0;
	a2 = (1.0f - alpha) / a0;
}

void HighPassFilterEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "frequency-cutoff") {
		freqCutOff = value;
		changeParameterLog("Frequency Cutoff", value);
	}
	else if (parameter == "q-factor") {
		QFactor = value;
		changeParameterLog("Q Factor", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void HighPassFilterEffect::getParameterInfo() {
	std::cout << "Frequency Cutoff: " << freqCutOff << std::endl;
	std::cout << "Q Factor: " << QFactor << std::endl;
}