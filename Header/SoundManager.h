#pragma once
#include <Singleton.h>
#include <CoreDefine.h>
#include <../ThirdParty/FMOD/inc/fmod.hpp>

#undef PlaySound
namespace Engine
{
	class SoundManager : public CoreBase, public Singleton<SoundManager>
	{
	private:
		friend class Singleton;

	private:
		SoundManager() = default;
		~SoundManager() = default;

	public:
		constexpr static int _inf = -1;

	public:
		bool Initialize(int maxChannels);
		void LoadSound(const char* filePath);
		void Update(_float deltaTime);

	public:
		void PlaySound(const char* soundName, int channel, int loopCount);
		void StopSound(int channel);
		void StopAllSound();

	public:
		void SetMasterVolume(float volume);
		void SetTargetVolume(int channel, float volume);
		void SetVolume(int channel, float volume);
		void SetMute(int channel, bool mute);
		void SetPause(int channel, bool pause);
		void SetPitch(int channel, float pitch);

	public:
		void SetPan(int channel, float pan);

	public:
		virtual void Destroy() override;

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	private:
		FMOD::System*									_pSystem{ nullptr };
		FMOD::ChannelGroup*								_pMasterChannelGroup{ nullptr };
		std::vector<FMOD::ChannelGroup*>				_channelGroups;
		std::list<FMOD::Channel*>						_excuteChannels;
		std::unordered_map<std::string, FMOD::Sound*>	_sounds;
		std::vector<FadeSound>							_fadeSounds;
		int												_maxChannels{ 0 };
	};
}

inline Engine::SoundManager* Sound = Engine::SoundManager::GetInstance();
inline std::function<void()> SoundTerminate = []() { Sound->Terminate(); };