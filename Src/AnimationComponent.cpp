#include <AnimationComponent.h>
#include <Actor.h>
#include <Mathf.h>
#include <Texture.h>
#include <TextureManager.h>
#include <ACollision.h>
#include <CoreDefine.h>
#include <CsvLoader.h>
#include <TimeManager.h>
#include <Animation.h>

#undef min
#undef max

void Engine::AnimationComponent::TickComponent(_duration deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);

	if (_isVisible == false) { return; }
	if (0 == _currentFrame) { _isFrameEnd = false; }

	_currentFrameTime += Time->NanoToSeconds(deltaSeconds);
	
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

	Animation* pAnimation = GetOwner()->GetAnimation(_currentClipIndex);

	SetAnimationRect(pAnimation);

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

	pRenderTarget->DrawBitmap((*pAnimation)[_currentFrame]);

	pRenderTarget->SetTransform(Matx::Identity);
}

void Engine::AnimationComponent::SetAnimationRect(Animation* pAnimation)
{
	Mathf::SizeF size = pAnimation->GetCanvasSize();

	_textureRect = Mathf::RectF{ 0, 0, size.width, size.height };
}

void Engine::AnimationComponent::AllAddClipThisActor()
{
	string ownerName = GetOwner()->GetName();
	_pwstring convertOwnerName = ownerName;

	for (const auto& [tag, animation] : TextureMgr->GetAnimations())
	{
		if (tag.find(convertOwnerName) != std::string::npos)
		{
			std::wstring clipName = tag.substr(tag.find_last_of(L"/") + 1);
			string convertClipName = clipName.c_str();
			AddClip(convertClipName, 0.1f, true);
		}
	}
}

void Engine::AnimationComponent::AddClip(_pstring clipName, _float frameTime, bool isLoop)
{
	if(!_isInLayer)
	{
		AddRenderQueueInLayer();
		_isInLayer = true;
	}

	string convertOwnerName = (string)"Assets/" + GetOwner()->GetName();
	string convertName = clipName;
	string textureName = convertOwnerName + "/" + convertName;

	Animation* pAnimation = TextureMgr->FindAnimation(textureName);
	AnimationClip* pClip = new AnimationClip(clipName);
	pClip->frameTime = frameTime;
	pClip->clipIndex = _indexCount++;
	pClip->maxFrame = pAnimation->size();
	pClip->isLoop = isLoop;

	_vecClips[clipName] = std::move(pClip);
	GetOwner()->AddAnimation(pAnimation);
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
	_frameCount = _vecClips[clipName]->maxFrame;
	_frameTime = _vecClips[clipName]->frameTime;
	_isLoop = _vecClips[clipName]->isLoop;

	Animation* pAnimation = GetOwner()->GetAnimation(_currentClipIndex);

	_frameCount = (int)pAnimation->size();

	_currentFrame = 0;
	_prevFrame = 0;
}

void Engine::AnimationComponent::RemoveClip(_pstring clipName)
{
	_vecClips.erase(clipName);
}

bool Engine::AnimationComponent::InitializeComponent()
{
	AllAddClipThisActor();

    return true;
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
