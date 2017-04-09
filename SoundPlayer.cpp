#include "DXUT.h"
#include "SoundPlayer.h"
#include "SDKsound.h"
#include "SDKwavefile.h"
#include <strsafe.h>
#include <shellapi.h>

SoundPlayer::SoundPlayer()
{
	
}

SoundPlayer::~SoundPlayer()
{
	
}

void SoundPlayer::Play(const std::wstring & music, bool loop)
{
	std::shared_ptr<Sound> newSound(new Sound());
	newSound->Play(music.c_str(),loop);

	sounds.push_back(newSound);
}

void SoundPlayer::Update()
{
	for (auto it = sounds.begin(); it < sounds.end();)
	{
		if (!(*it)->isRunning)
		{
			sounds.erase(it);
		}
		else { it++; }
	}

	for (size_t i = 0; i < sounds.size(); i++)
	{
		sounds[i]->Update();
	}
}

Sound::Sound()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	XAudio2Create(&audio);

	audio->CreateMasteringVoice(&masteringVoice);
}

Sound::~Sound()
{
	sourceVoice->DestroyVoice();
	SAFE_DELETE_ARRAY(waveData);

	masteringVoice->DestroyVoice();
	SAFE_RELEASE(audio);

	CoUninitialize();
}

void Sound::Play(LPCWSTR szFilename, bool loop)
{

	WCHAR strFilePath[MAX_PATH];
	FindMediaFileCch(strFilePath, MAX_PATH, szFilename);

	CWaveFile wav;
	wav.Open(strFilePath, NULL, WAVEFILE_READ);

	WAVEFORMATEX* pwfx = wav.GetFormat();

	DWORD cbWaveSize = wav.GetSize();

	waveData = new BYTE[cbWaveSize];
	wav.Read(waveData, cbWaveSize, &cbWaveSize);

	audio->CreateSourceVoice(&sourceVoice, pwfx);

	XAUDIO2_BUFFER buffer = { 0 };
	buffer.pAudioData = waveData;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = cbWaveSize;
	if (loop)
	{
		buffer.LoopCount = pow(2,32);
	}

	sourceVoice->SubmitSourceBuffer(&buffer);

	sourceVoice->Start(0);
}

HRESULT Sound::FindMediaFileCch(WCHAR * strDestPath, int cchDest, LPCWSTR strFilename)
{
	bool bFound = false;

	if (NULL == strFilename || strFilename[0] == 0 || NULL == strDestPath || cchDest < 10)
		return E_INVALIDARG;

	// Get the exe name, and exe path
	WCHAR strExePath[MAX_PATH] = { 0 };
	WCHAR strExeName[MAX_PATH] = { 0 };
	WCHAR* strLastSlash = NULL;
	GetModuleFileName(NULL, strExePath, MAX_PATH);
	strExePath[MAX_PATH - 1] = 0;
	strLastSlash = wcsrchr(strExePath, TEXT('\\'));
	if (strLastSlash)
	{
		wcscpy_s(strExeName, MAX_PATH, &strLastSlash[1]);

		// Chop the exe name from the exe path
		*strLastSlash = 0;

		// Chop the .exe from the exe name
		strLastSlash = wcsrchr(strExeName, TEXT('.'));
		if (strLastSlash)
			*strLastSlash = 0;
	}

	wcscpy_s(strDestPath, cchDest, strFilename);
	if (GetFileAttributes(strDestPath) != 0xFFFFFFFF)
		return S_OK;

	// Search all parent directories starting at .\ and using strFilename as the leaf name
	WCHAR strLeafName[MAX_PATH] = { 0 };
	wcscpy_s(strLeafName, MAX_PATH, strFilename);

	WCHAR strFullPath[MAX_PATH] = { 0 };
	WCHAR strFullFileName[MAX_PATH] = { 0 };
	WCHAR strSearch[MAX_PATH] = { 0 };
	WCHAR* strFilePart = NULL;

	GetFullPathName(L".", MAX_PATH, strFullPath, &strFilePart);
	if (strFilePart == NULL)
		return E_FAIL;

	while (strFilePart != NULL && *strFilePart != '\0')
	{
		swprintf_s(strFullFileName, MAX_PATH, L"%s\\%s", strFullPath, strLeafName);
		if (GetFileAttributes(strFullFileName) != 0xFFFFFFFF)
		{
			wcscpy_s(strDestPath, cchDest, strFullFileName);
			bFound = true;
			break;
		}

		swprintf_s(strFullFileName, MAX_PATH, L"%s\\%s\\%s", strFullPath, strExeName, strLeafName);
		if (GetFileAttributes(strFullFileName) != 0xFFFFFFFF)
		{
			wcscpy_s(strDestPath, cchDest, strFullFileName);
			bFound = true;
			break;
		}

		swprintf_s(strSearch, MAX_PATH, L"%s\\..", strFullPath);
		GetFullPathName(strSearch, MAX_PATH, strFullPath, &strFilePart);
	}
	if (bFound)
		return S_OK;

	// On failure, return the file as the path but also return an error code
	wcscpy_s(strDestPath, cchDest, strFilename);

	return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
}

void Sound::Update()
{
	if (isRunning)
	{
		XAUDIO2_VOICE_STATE state;
		sourceVoice->GetState(&state);
		isRunning = (state.BuffersQueued > 0) != 0;
	}
}
