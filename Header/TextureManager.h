#pragma once
#include <CoreDefine.h>
#include <Singleton.h>
#include <ObjectPtr.h>

namespace Engine
{
	CORECLASS()
	class TextureManager : public CoreBase, public Singleton<TextureManager>
	{
	private:
		friend class Singleton;

	private:
		using Textures = std::unordered_map<std::wstring, ObjectPtr<Texture>>;

	private:
		TextureManager() = default;
		~TextureManager() = default;

	public:
		bool LoadTexture(LPCWSTR filePath);
		Texture* FindTexture(_pwstring fileTag);
		Textures& GetTextures() { return _textures; }

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	private:
		void Destroy() override;

	private:
		Textures _textures;
	};
}

inline Engine::TextureManager* TextureMgr = Engine::TextureManager::GetInstance();
inline std::function<void()> TextureTerminate = []() { TextureMgr->Terminate(); };