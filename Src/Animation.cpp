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
    _frameRate = 1 / _animation->frameRate();

    for (size_t frameNumber = 0; frameNumber < _totalFrame; ++frameNumber) 
    {
        std::vector<uint32_t> frameBuffer(_width * _height);
        rlottie::Surface surface(frameBuffer.data(), _width, _height, _width * 4);
        _animation->renderSync(frameNumber, surface);

        HRESULT hresult{ S_FALSE };

		SmartPtr<IWICBitmap>  pWICBitmap{ nullptr };
        SmartPtr<ID2D1Bitmap> pBitmap{ nullptr };
        hresult = Management->WICFactory->CreateBitmapFromMemory(
			_width,
			_height,
			GUID_WICPixelFormat32bppPBGRA,
			_width * 4,
			static_cast<UINT>(frameBuffer.size() * sizeof(uint32_t)),
			reinterpret_cast<BYTE*>(frameBuffer.data()),
			&pWICBitmap
		);
		if (SUCCEEDED(hresult))
		{
			hresult = Management->renderTarget->CreateBitmapFromWicBitmap(
				pWICBitmap.Get(), nullptr, &pBitmap);

			if (SUCCEEDED(hresult))
                _textures.push_back(pBitmap);
		}
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
