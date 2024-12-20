#pragma once
#include <iostream>
#include "portaudio.h"
#include "AudioProcessor.h"

class AudioManager {
private:

	PaStream* stream = nullptr;
	AudioProcessor audioProcessor;

	double sampleRate;
	unsigned long bufferSize;
	int channel;

	static int audioCallback(const void* input, void* output, unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

public:
	AudioManager(double sr, unsigned long bs, int ch);
	~AudioManager();
	void openStream(int device1, int device2);
	void closeStream();
	void switchDevice(int device1, int device2);
	void terminatePortAudio();
	AudioProcessor& getAudioProcessor();

};