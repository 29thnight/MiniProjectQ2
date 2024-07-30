#include <AnimationComponent.h>
#include <Actor.h>
#include <Mathf.h>
#include <Texture.h>
#include <TextureManager.h>
#include <ACollision.h>
#include <CoreDefine.h>
#include <CsvLoader.h>

#undef min
#undef max

void Engine::AnimationComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);

	if (_isVisible == false) { return; }
	if (0 == _currentFrame) { _isFrameEnd = false; }

	_currentFrameTime += deltaSeconds;
	
	if (_currentFrameTime >= _frameTime)
	{
		_currentFrameTime -= _frameTime;
		_prevFrame = _currentFrame;

		if (_isLoop)
		{
			_currentFrame = (_currentFrame + 1) % _frameCount;
		}
		else
		{
			_currentFrame = std::min(_currentFrame + 1, _frameCount - 1);
		}
	}

	if (_prevFrame != _currentFrame && _currentFrame == _frameCount - 1)
	{
		_isFrameEnd = true;
	}
	else
	{
		_isFrameEnd = false;
	}
}

void Engine::AnimationComponent::Render(_RenderTarget pRenderTarget)
{
	if (_isVisible == false) { return; }

	Texture* pTexture = GetOwner()->GetFrame(_currentClipIndex);

	SetTextureRect(pTexture);

	SetBitmapLocalTransform();

	Mathf::Matx3F flipMatrix = Matx::Identity;

	if (_isFlip)
	{
		flipMatrix = Mathf::Scale(Mathf::Vector2{-1.f, 1.f}, 
			Mathf::Point2F{_textureRect.right * 0.5f, _textureRect.bottom * 0.5f}) * _localTransform;
	}
	else
	{
		flipMatrix = _localTransform;
	}

	Mathf::Matx3F Transform = flipMatrix * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);

	pRenderTarget->DrawBitmap((*pTexture)[_currentFrame]);

	pRenderTarget->SetTransform(Matx::Identity);
}

void Engine::AnimationComponent::AllAddClipThisActor()
{
	string BasePath = (string)"Assets/" + GetOwner()->GetName();
	string convertDataName = BasePath + "/Clips.csv";
	CSVReader<std::string, float, bool> csvReader((_pstring)convertDataName);

	csvReader.forEach([&](std::string clipName, float frameTime, bool isLoop)
		{
			AddClip(clipName.c_str(), frameTime, isLoop);
		});
}

void Engine::AnimationComponent::AddClip(_pstring clipName, _float frameTime, bool isLoop)
{
	if(!_isInLayer)
	{
		AddRenderQueueInLayer();
		_isInLayer = true;
	}

	AnimationClip* pClip = new AnimationClip(clipName);
	pClip->frameTime = frameTime;
	pClip->clipIndex = (int)GetOwner()->GetTextureSize();
	pClip->isLoop = isLoop;

	_vecClips[clipName] = std::move(pClip);
	string convertOwnerName = (string)"Assets/" + GetOwner()->GetName();
	string convertName = clipName;
	string textureName = convertOwnerName + "/" + convertName;
	
	GetOwner()->AddTexture(TextureMgr->FindTexture(textureName));
}

const bool Engine::AnimationComponent::IsClipPlay(_pstring clipName) const
{
	if (_currentClipName && !strcmp(_currentClipName, clipName))
	{
		return !_isFrameEnd;
	}

	return false;
}

const bool Engine::AnimationComponent::IsClipEnd(_pstring clipName) const
{
	if (_currentClipName && !strcmp(_currentClipName, clipName))
	{
		return _isFrameEnd;
	}

	return true;
}

const bool Engine::AnimationComponent::IsFrameEnd() const
{
	return _isFrameEnd;
}

void Engine::AnimationComponent::SetPlayClip(_pstring clipName)
{
	_currentClipName = clipName;
	_currentClipIndex = _vecClips[clipName]->clipIndex;
	_frameTime = _vecClips[clipName]->frameTime;
	_isLoop = _vecClips[clipName]->isLoop;

	Texture* pTexture = GetOwner()->GetFrame(_currentClipIndex);

	_frameCount = (int)pTexture->size();

	_currentFrame = 0;
	_prevFrame = 0;
}

void Engine::AnimationComponent::RemoveClip(_pstring clipName)
{
	_vecClips.erase(clipName);
}

bool Engine::AnimationComponent::InitializeComponent()
{
    return BitmapComponent::InitializeComponent();
}

void Engine::AnimationComponent::Destroy()
{
	for (auto& clip : _vecClips)
	{
		delete clip.second;
	}
	_vecClips.clear();
}

Engine::AnimationComponent* Engine::AnimationComponent::Create()
{
	return new AnimationComponent;
}
