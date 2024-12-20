#include <iostream>
#include "PitchShiftEffect.h"
#include "SoundTouch.h"

PitchShiftEffect::PitchShiftEffect(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;

	effectName = "Pitch Shift";
	effectAlias = "pitch-effect";
	effectDescription = "Pitch Shift Effect shifts the pitch of the audio.";

	pitch = 0;

	effectStatus = false;
	pitchEffectManager.setPitchSemiTones(pitch);
	pitchEffectManager.setSampleRate((unsigned long)sampleRate);
	pitchEffectManager.setChannels(1);

}

void PitchShiftEffect::process(float* input) {
	pitchEffectManager.putSamples(input, bufferSize);
	pitchEffectManager.receiveSamples(input, bufferSize);
}

void PitchShiftEffect::changeParameter(std::string parameter, float value) {
	if (parameter == "pitch") {
		pitch = value;
		pitchEffectManager.setPitchSemiTones(value);
		changeParameterLog("Pitch", value);
	}
	else {
		changeParameterInvalidLog(parameter);
	}
}

void PitchShiftEffect::getParameterInfo() {
	std::cout << "Pitch: " << pitch << std::endl;
}