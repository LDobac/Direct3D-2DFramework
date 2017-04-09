#pragma once

#include "Singleton.h"
#include <xAudio2.h>
#include <vector>
#include <memory>

class Sound
{
private:
	IXAudio2* audio = nullptr;
	IXAudio2SourceVoice* sourceVoice = nullptr;
	IXAudio2MasteringVoice* masteringVoice = nullptr;
	BYTE* waveData = nullptr;
public:
	Sound();
	~Sound();

	bool isRunning = true;
	bool isLoop = true;

	void Play(LPCWSTR szFilename,bool loop);
	HRESULT FindMediaFileCch(WCHAR* strDestPath, int cchDest, LPCWSTR strFilename);

	void Update();
};

class SoundPlayer
	: public Singleton<SoundPlayer>
{
private:
	std::vector<std::shared_ptr<Sound>> sounds;
public:
	SoundPlayer();
	~SoundPlayer();

	void Play(const std::wstring& music,bool loop);
	void Stop();

	void Update();
};