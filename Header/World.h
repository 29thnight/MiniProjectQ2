#pragma once
#include <CoreDefine.h>
#include <Mathf.h>

namespace Engine
{
	CORECLASS()
	class World abstract : public CoreBase
	{
	public:
		using Levels = std::vector<Level*>;
		using Layers = std::vector<Layer*>;
		using ActorMap = std::unordered_map<_pstring, Actor*>;

	protected:
		explicit World() = default;
		virtual	~World() = default;
	
	public:
		bool InitializeWorld(int layerSize);
		bool BeginPlayEnd();
		ReadOnly_Property(bool, isBeginPlayEnd);
		_Get(isBeginPlayEnd)
		{
			return World::BeginPlayEnd();
		}
		virtual void Destroy() override;

	public:
		virtual bool BeginPlay() PURE;
		virtual void Tick(_float deltaSeconds);
		virtual void Fixed();
		virtual void Render(_RenderTarget pRenderTarget);
		virtual void EndPlay();

	public:
		//level
		template<typename T>
		T* AddLevel()
		{
			T* pLevel = T::Create();
			ContainLevel(pLevel);
			return pLevel;
		}

		Level* GetLevel(int levelIndex) const;
		void ContainLevel(Level* pLevel);
		void RemoveLevel(int levelIndex);
		void ClearLevel();
		int GetLevelSize() const { return (int)_vecLevels.size(); }

	public:
		//Layer
		bool InitializeLayer(int layerSize);
		Layer* GetLayer(int layerIndex) const;
		void AddLayer(int layerIndex, Layer* pLayer);
		void RemoveLayer(int layerIndex);
		void ClearLayer();
		int GetLayerSize() const { return _layerSize; }

	public:
		//RenderSort
		virtual void CustomRenderSort() {};
		void SetCustomRenderSort(bool isCustomRenderSort) { _isCustomRenderSort = isCustomRenderSort; }
		void SetSortGreater(bool isSortGreater) { _isSortGreater = isSortGreater; }
		bool IsCustomRenderSort() const { return _isCustomRenderSort; }
		bool IsSortGreater() const { return _isSortGreater; }

	public:
		//Camera
		CameraActor* GetCameraActor() { return _pCameraActor; }
		void SettingCamera(CameraActor* pCameraActor = nullptr);
		void SettingCameraPosition(Mathf::Vector2 position);
		void SettingTrackingCameraTarget(Actor* pTargetActor);
		void SetCameraLerpFactor(float lerpFactor);
		void SettingTrackingCamera(bool isTracking);
		bool IsTrackingCamera() const;
		void SettingCameraOffset(Mathf::Vector2 offset);

	public:
		//WorldSize
		void SetWorldSize(Mathf::RectF worldSize) { _worldSize = worldSize; }
		Mathf::RectF GetWorldSize() const { return _worldSize; }

	public:
		//Actor
		ActorMap& GetActorMap() { return _actorMap; }
		Actor* FindActor(_pstring name);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location);
		bool RemoveActor(_pstring name);
		bool ReviveActor(_pstring name);

	private:
		void DebugDrawGrid(_RenderTarget pRenderTarget);

	protected:
		CoreManager* _pCoreManager{ nullptr };
		CameraActor* _pCameraActor{ nullptr };
		Canvas*		 _pCanvas{ nullptr };

	protected:
		ActorMap _actorMap;
		Levels	 _vecLevels;
		Layers	 _vecLayers;

	protected:
		Mathf::Matx3F	_worldTransform{ Matx::Identity };
		Mathf::Vector2	_worldCenter{ UnitVector::Zero };
		Mathf::RectF	_worldSize{};

	protected:
		int	 _currentLevelIndex{};
		int	 _layerSize{};
		bool _isCustomRenderSort{ false };
		bool _isSortGreater{ false };
	};
}