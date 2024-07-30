#pragma once
#include <CoreDefine.h>
#include <Object.h>
#include <Mathf.h>
#include <IColliderReceiver.h>
#include <ObjectPtr.h>
#include <ISetupInputComponent.h>

namespace Engine
{
	CORECLASS()
	class Actor abstract : public Object, public IColliderReceiver, public ISetupInputComponent
	{
	protected:
		explicit Actor() = default;
		virtual ~Actor() = default;

	public:
		virtual void BeginPlay() abstract;
		virtual void Tick(_float deltaSeconds) abstract;
		virtual void Fixed() abstract;
		virtual void EndPlay() abstract;
		virtual void NotifyActorBlock(CollisionData data) override {};
		virtual void NotifyActorBeginOverlap(CollisionData data) override {};
		virtual void NotifyActorEndOverlap(CollisionData data) override {};
		virtual void SetupInputComponent(InputComponent* inputComponent) override {};
		virtual void ReviveInitialize() {};

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		template <typename T>
		T* AddComponent(_pstring name)
		{
			static_assert(std::is_base_of<ActorComponent, T>::value, "T must derive form Component");

			T* pComponent = T::Create();
			pComponent->SetOwner(this);
			pComponent->SetName(name);

			bool isSceneComponent = std::is_base_of<SceneComponent, T>::value;
			bool isRootComponent = (nullptr == _pRootComponent);
			if (isSceneComponent && !isRootComponent)
			{
				SceneComponent* pSceneComponent = dynamic_cast<SceneComponent*>(pComponent);
				pSceneComponent->AttachToComponent(_pRootComponent);
			}
			pComponent->InitializeComponent();
			ObjectPtr<ActorComponent> pComponentPtr(pComponent);
			_vecComponents.push_back(std::move(pComponentPtr));
			return pComponent;
		}

		template <typename T>
		T* GetComponent(_pstring name)
		{
			for (auto& component : _vecComponents)
			{
				if (!strcmp(component->GetName(),name))
					return dynamic_cast<T*>(component.Get());
			}
			return nullptr;
		}

	public:
		bool operator==(_pstring name) const { return !strcmp(this->_name, name); }
		bool operator!=(_pstring name) const { return strcmp(this->_name, name); }

	public:
		bool SetRootComponent(SceneComponent* pRootComponent);
		SceneComponent* GetRootComponent() const { return _pRootComponent; }

	public:
		void SetLayerIndex(int layerIndex) { _layerIndex = layerIndex; }
		int GetLayerIndex() const { return _layerIndex; }

	public:
		void AttachToActor(Actor* pParent);
		void DetachFromActor();
		Actor* GetParent() const { return _pParent; }

	public:
		void SetWorld(World* world) { _pOwnerWorld = world; }
		World* GetWorld() const { return _pOwnerWorld; }

	public:
		void AddTexture(Texture* pTexture) { _vecTextures.push_back(pTexture); }
		size_t GetTextureSize() const { return _vecTextures.size(); }
		Texture* GetFrame(int index) const { return _vecTextures[index]; }

	protected:
		void PushBackComponent(ActorComponent* pComponent);

	protected:
		void Destroy() override;

	protected:
		SceneComponent*	_pRootComponent{ nullptr };
		Actor*			_pParent{ nullptr };
		World*			_pOwnerWorld{ nullptr };
		int				_layerIndex{ 0 };

	protected:
		std::vector<Actor*>						_vecChildren;
		std::vector<ObjectPtr<ActorComponent>>	_vecComponents;
		std::vector<Texture*>					_vecTextures;
	};
}