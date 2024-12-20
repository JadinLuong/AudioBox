#include <iostream>
#include <iomanip>
#include "BitCrushingEffect.h"

BitCrushingEffect::BitCrushingEffect(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;
	effectName = "Bit Crushing";
	effectAlias = "bit-crush-effect";
	effectDescription = "Bit Crushing Effect will distort the audio giving a lower quality sounding audio.";
	bitDepth = 4;
	effectStatus = false;
}

void BitCrushingEffect::process(float* input) {

	for (unsigned long i = 0; i < bufferSize; i++) {
		float maxVal = pow(2, bitDepth) - 1;
		input[i] = round(input[i] * maxVal) / maxVal;
	}
}

void BitCrushingEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "bit-depth") {
		bitDepth = value;
		changeParameterLog("Bit Depth", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void BitCrushingEffect::getParameterInfo() {
	std::cout << "Depth: " << bitDepth << "\n";
}