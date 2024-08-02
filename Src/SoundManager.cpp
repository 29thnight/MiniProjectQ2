#include <CoreDefine.h>
#include <SoundManager.h>
#include <TimeManager.h>

namespace file = std::filesystem;

bool Engine::SoundManager::Initialize(int maxChannels)
{
	int numberOfAvailableChannels{};

	FMOD::System_Create(&_pSystem);
	_pSystem->getSoftwareChannels(&numberOfAvailableChannels);
	_pSystem->init(maxChannels, FMOD_INIT_NORMAL, nullptr);

	_maxChannels = maxChannels;
	_channelGroups.resize(maxChannels);
	_fadeSounds.resize(maxChannels);
	_pSystem->getMasterChannelGroup(&_pMasterChannelGroup);

	for (int i = 0; i < maxChannels; ++i)
	{
		_pSystem->createChannelGroup(nullptr, &_channelGroups[i]);
		_pMasterChannelGroup->addGroup(_channelGroups[i]);
	}

	return true;
}

void Engine::SoundManager::LoadSound(const char* filePath)
{
	file::path rootPath(filePath);

	for(const auto& entry : file::directory_iterator(rootPath))
	{
		if (entry.is_directory())
		{
			if (entry.path().filename() == "." || entry.path().filename() == "..")
				continue;

			LoadSound(entry.path().string().c_str());
		}
		else
		{
			file::path fullPath = entry.path();

			std::string tag = fullPath.parent_path().string();
			tag = tag.substr(tag.find_last_of("/") + 1);
			std::replace(tag.begin(), tag.end(), '\\', '/');

			FMOD::Sound* pSound = _sounds[tag];

			if (nullptr == pSound)
			{
				_pSystem->createSound(fullPath.string().c_str(), FMOD_DEFAULT, nullptr, &pSound);
				_sounds[tag] = pSound;
			}
		}
	}
}

void Engine::SoundManager::Update(_float deltaTime)
{
	_pSystem->update();
	for (int i = 0; i < _maxChannels; ++i)
	{
		if (_fadeSounds[i].current >= _fadeSounds[i].target)
		{
			_fadeSounds[i].current -= deltaTime;
		}
		_channelGroups[i]->setVolume(_fadeSounds[i].current);
	}

	for (auto& channel : _excuteChannels)
	{
		bool isPlaying = false;
		channel->isPlaying(&isPlaying);

		if (!isPlaying)
		{
			_excuteChannels.remove(channel);
		}
	}
}

void Engine::SoundManager::PlaySound(const char* soundName, int channel, int loopCount)
{
	FMOD::Sound* pSound = _sounds[soundName];

	if(pSound)
	{
		FMOD::Channel* pChannel = nullptr;
		_excuteChannels.push_back(pChannel);

		_pSystem->playSound(pSound, _channelGroups[channel], false, &pChannel);
		pChannel->setLoopCount(loopCount);
		_excuteChannels.push_back(pChannel);
	}
}

void Engine::SoundManager::StopSound(int channel)
{
	_channelGroups[channel]->stop();
}

void Engine::SoundManager::StopAllSound()
{
	_pMasterChannelGroup->stop();
}

void Engine::SoundManager::SetMasterVolume(float volume)
{
	_pMasterChannelGroup->setVolume(volume);
}

void Engine::SoundManager::SetTargetVolume(int channel, float volume)
{
	_fadeSounds[channel].target = volume;
}

void Engine::SoundManager::SetVolume(int channel, float volume)
{
	_fadeSounds[channel].current = volume;
	_fadeSounds[channel].target = volume;
}

void Engine::SoundManager::SetMute(int channel, bool mute)
{
	_channelGroups[channel]->setMute(mute);
}

void Engine::SoundManager::SetPause(int channel, bool pause)
{
	_channelGroups[channel]->setPaused(pause);
}

void Engine::SoundManager::SetPitch(int channel, float pitch)
{
	_channelGroups[channel]->setPitch(pitch);
}

void Engine::SoundManager::SetPan(int channel, float pan)
{
	_channelGroups[channel]->setPan(pan);
}

_uint Engine::SoundManager::GetPosition(int channel)
{
	if (channel < 0 || channel >= _maxChannels) 
	{
        return 0;  // 잘못된 채널 번호 처리
    }

    _uint position = 0;
    FMOD::Channel* pChannel = nullptr;
    _channelGroups[channel]->getChannel(0, &pChannel);

    if (pChannel)
	{
        pChannel->getPosition(&position, FMOD_TIMEUNIT_MS);
    }

    return position;
}

void Engine::SoundManager::Destroy()
{
	for (auto& sound : _sounds)
	{
		sound.second->release();
	}

	for (auto& channelGroup : _channelGroups)
	{
		channelGroup->release();
	}

	_pMasterChannelGroup->release();

	_pSystem->close();
	_pSystem->release();

	_sounds.clear();
}
