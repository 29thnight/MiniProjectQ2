#pragma once
#include <SceneComponent.h>
#include <ObjectPtr.h>
#include <ACollision.h>

namespace Engine
{
	CORECLASS()
	class CameraComponent : public SceneComponent
	{
	protected:
		explicit CameraComponent() = default;
		virtual ~CameraComponent() = default;
	public:
		virtual bool InitializeComponent() override;
		virtual void BeginPlay() override {};
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void EndPlay() override {};

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		void SetCenterPosition(Mathf::Vector2 centerPosition) { _centerPosition = centerPosition; }
		Mathf::Vector2 GetCenterPosition() const { return _centerPosition; }

		void SetCameraSize(Mathf::Vector2 cameraSize) { _cameraSize = cameraSize; }
		Mathf::Vector2 GetCameraSize() const { return _cameraSize; }

		void SetCameraOffset(Mathf::Vector2 cameraOffset) { _cameraOffset = cameraOffset; }
		Mathf::Vector2 GetCameraOffset() const { return _cameraOffset; }

		void SetCameraZoomScale(Mathf::Vector2 cameraZoomScale) { _cameraZoomScale = cameraZoomScale; }
		Mathf::Vector2 GetCameraZoomScale() const { return _cameraZoomScale; }

		bool CheckCollision(ACollision* pCollision);

	protected:
		virtual void Destroy();

	public:
		static CameraComponent* Create();

	private:
		Mathf::Matx3F		  _cameraMatrix	   { Matx::Identity };
		Mathf::Vector2		  _cameraZoomScale { UnitVector::One };
		Mathf::Vector2		  _centerPosition  { UnitVector::Zero };
		Mathf::Vector2		  _cameraSize	   { UnitVector::Zero };
		Mathf::Vector2		  _cameraOffset	   { UnitVector::Zero };
		ACollision*			  _pCollision	   { nullptr };
	};
}