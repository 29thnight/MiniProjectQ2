#pragma once
#include <CoreDefine.h>
#include <CollisionComponent.h>

namespace Engine
{
	class BoxComponent : public CollisionComponent
	{
	protected:
		explicit BoxComponent() = default;
		virtual ~BoxComponent() = default;

	public:
		virtual bool InitializeComponent() override;
		virtual void TickComponent(_float deltaSeconds) override;
		virtual bool IsCollision(CollisionComponent* pOther) override;
		virtual void Render(_RenderTarget pRenderTarget) override; //for debug draw
	
	public:
		void SetAddOffset(const Mathf::Vector2& offsetVector); 
		void SetSize(const Mathf::Vector2& sizeVector);

	public:
		void Remove();
	
	public:
		static BoxComponent* Create();

	protected:
		ACollision*	   _pCollision{ nullptr };
		Mathf::Vector2 _addOffset{ 0.f, 0.f };
	};
}