#pragma once
#include <CoreBase.h>
#include <CoreDefine.h>

namespace Engine
{
	class Texture : public CoreBase
	{
	protected:
		explicit Texture() = default;
		virtual ~Texture() = default;

	public:
		ID2D1Bitmap* operator[](_uint index) { return _textures[index].Get(); }

	public:
		ID2D1Bitmap* LoadTexture(_pwstring fileName);
		size_t size() const { return _textures.size(); }

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		static Texture* Create();
		void Destroy() override;

	private:
		string _path{};
		std::vector<SmartPtr<ID2D1Bitmap>> _textures{};
	};
}