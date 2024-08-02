#include <Animation.h>
#include <CoreManager.h>

bool Engine::Animation::LoadAnimation(_pwstring fileName)
{
    string convert = fileName;
    _path = convert;
    _animation = rlottie::Animation::loadFromFile(_path);

    if (!_animation) return false;

    _animation->size(_width, _height);
    _totalFrame = _animation->totalFrame();
    _frameRate = _animation->frameRate();

    for (size_t frameNumber = 0; frameNumber < _totalFrame; ++frameNumber) 
    {
        std::vector<uint32_t> frameBuffer(_width * _height);
        rlottie::Surface surface(frameBuffer.data(), _width, _height, _width * 4);
        _animation->renderSync(frameNumber, surface);

        D2D1_BITMAP_PROPERTIES bitmapProperties{ };
        bitmapProperties.pixelFormat = Management->renderTarget->GetPixelFormat();
        bitmapProperties.dpiX = bitmapProperties.dpiY = 96.0f;

        ID2D1Bitmap* pBitmap = nullptr;
        Management->renderTarget->CreateBitmap(
            D2D1::SizeU((UINT32)_width, (UINT32)_height),
            frameBuffer.data(),
            _width * 4,
            &bitmapProperties,
            &pBitmap
        );

        _textures.push_back(pBitmap);
    }

        return true;
}

Mathf::SizeF Engine::Animation::GetCanvasSize() const
{
	return Mathf::SizeF{ (float)_width, (float)_height };
}

Engine::Animation* Engine::Animation::Create()
{
	return new Animation;
}

void Engine::Animation::Destroy()
{
}
