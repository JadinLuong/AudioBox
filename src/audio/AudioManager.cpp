#include <iostream>
#include "portaudio.h"
#include "AudioManager.h"
#include "AudioProcessor.h"
#include "../utils/Logger.h"

AudioManager::AudioManager(double sr, unsigned long bs, int ch) {
	audioProcessor = AudioProcessor(sr, bs);

	sampleRate = sr;
	bufferSize = bs;
	channel = ch;

	PaError err = Pa_Initialize();

	if (err != paNoError) {
		std::cerr << "PortAudio Initialize Error: " << Pa_GetErrorText(err) << std::endl;
	}
}

AudioManager::~AudioManager() {
	closeStream();
	terminatePortAudio();
}

void AudioManager::openStream(int device1, int device2) {

	PaStreamParameters inputParameters, outputParameters;

	if (stream) {
		std::cerr << "Stream is already opened" << std::endl;
		return;
	}

	inputParameters.device = device1;
	inputParameters.channelCount = channel;
	inputParameters.sampleFormat = paFloat32;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = nullptr;

	outputParameters.device = device2;
	outputParameters.channelCount = channel;
	outputParameters.sampleFormat = paFloat32;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = nullptr;

	PaError err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, sampleRate, bufferSize, paClipOff, audioCallback, &audioProcessor);

	if(err != paNoError){
		std::cerr << "Failed to open audio stream: " << Pa_GetErrorText(err) << std::endl;
		return;
	}

	err = Pa_StartStream(stream);

	if (err != paNoError) {
		std::cerr << "Failed to start audio stream: " << Pa_GetErrorText(err) << std::endl;
		return;
	}
}

void AudioManager::closeStream() {

	if (stream) {
		PaError err = Pa_StopStream(stream);

		if (err != paNoError) {
			std::cerr << "Failed to stop audio stream: " << Pa_GetErrorText(err) << std::endl;
		}

		err = Pa_CloseStream(stream);

		if (err != paNoError) {
			std::cerr << "Failed to close audio stream: " << Pa_GetErrorText(err) << std::endl;
		}
	}

	stream = nullptr;
}

void AudioManager::terminatePortAudio() {
	PaError err = Pa_Terminate();
		
	if (err != paNoError) {
		std::cerr << "Failed to terminate PortAudio: " << Pa_GetErrorText(err) << std::endl;
	}
}

void AudioManager::switchDevice(int device1, int device2) {
	closeStream();
	openStream(device1, device2);
}

int AudioManager::audioCallback(const void* input, void* output, unsigned long frames,
	const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData) {
	float* in = (float*)input;
	float* out = static_cast<float*>(output);

	AudioProcessor* audioProcessor = (AudioProcessor*)userData;
	audioProcessor->applyEffects(in);

	for (unsigned long i = 0; i < frames; i++) {
		out[i] = in[i];
	}

	return paContinue;
}

AudioProcessor& AudioManager::getAudioProcessor() {
	return audioProcessor;
}