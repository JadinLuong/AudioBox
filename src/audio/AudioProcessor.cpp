#include <iostream>
#include <vector>
#include "portaudio.h"
#include "AudioProcessor.h"
#include "../effects/EffectsHeaders.h"

AudioProcessor::AudioProcessor() {

}

AudioProcessor::AudioProcessor(double sr, unsigned long bs) {
	sampleRate = sr;
	bufferSize = bs;
	initializeEffects();
}

AudioProcessor::~AudioProcessor() {

}

void AudioProcessor::changeParameter(std::string effectName, std::string parameter, float value) {
	if (audioEffects.find(effectName) != audioEffects.end()) {
		AudioEffect* effect = audioEffects[effectName];
		effect->changeParameter(parameter, value);
	}
	else {
		std::cout << "\'" + effectName + "\'" + " is not a valid effect.\n\n";
	}
}

void AudioProcessor::applyEffects(float* input) {
;	for (int i = 0; i < processingChain.size(); i++) {
		processingChain[i]->process(input);
	}
}

void AudioProcessor::toggleEffect(std::string effectName) {
	if (audioEffects.find(effectName) != audioEffects.end()) {
		AudioEffect* effect = audioEffects[effectName];
		if (effect->isEffectOn()) {
			for (int i = 0; i < processingChain.size(); i++) {
				if (effect == processingChain[i]) {
					processingChain.erase(processingChain.begin() + i);
;				}
			}
			effect->disable();
			Logger::getInstance().print(effect->getEffectName() + " has been toggled OFF.\n");
		}
		else {
			processingChain.push_back(effect);
			effect->enable();
			Logger::getInstance().print(effect->getEffectName() + " has been toggled ON.\n");
		}
	}
	else {
		std::cout << effectName << " does not exist.\n";
	}
}

void AudioProcessor::initializeEffects() {
	audioEffects["ring-mod-effect"] = new RingModEffect(sampleRate, bufferSize);
	audioEffects["pitch-effect"] = new PitchShiftEffect(sampleRate, bufferSize);
	audioEffects["delay-effect"] = new DelayEffect(sampleRate, bufferSize);
	audioEffects["chorus-effect"] = new ChorusEffect(sampleRate, bufferSize);
	audioEffects["hpf-effect"] = new HighPassFilterEffect(sampleRate, bufferSize);
	audioEffects["lpf-effect"] = new LowPassFilterEffect(sampleRate, bufferSize);
	audioEffects["bit-crush-effect"] = new BitCrushingEffect(sampleRate, bufferSize);
}

std::map<std::string, AudioEffect*>& AudioProcessor::getAudioEffects() {
	return audioEffects;
}