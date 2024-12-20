#pragma once
#include <iostream>
#include "AudioEffect.h"
#include <SoundTouch.h>

class PitchShiftEffect : public AudioEffect {
private:
	float pitch;
	soundtouch::SoundTouch pitchEffectManager;
public:
	PitchShiftEffect(double sr, unsigned long bs);
	void process(float* input);
	void changeParameter(std::string parameter, float value);
	void getParameterInfo();
};