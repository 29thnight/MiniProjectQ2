#include <Animation.h>
#include <CoreManager.h>
#include "../ThirdParty/nlohmann/json.hpp"

bool Engine::Animation::LoadAnimation(_pwstring fileName)
{
    HRESULT hresult{ S_FALSE };
    string  convert = fileName;

    _path = convert;

	std::string metaFilePath = _path.substr(0, _path.find_last_of('.')) + ".metadata";
    std::ifstream inputFile(metaFilePath);
	if (inputFile.is_open())
	{
		nlohmann::json json;
		inputFile >> json;
		inputFile.close();

		if (json.contains("loop"))
		{
			_isLoop = json["loop"].get<bool>();
		}
	}

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

		SmartPtr<IWICBitmap>  pWICBitmap{ nullptr };
        SmartPtr<ID2D1Bitmap> pBitmap{ nullptr };
        hresult = Management->WICFactory->CreateBitmapFromMemory(
			(_uint)_width,
			(_uint)_height,
			GUID_WICPixelFormat32bppPBGRA,
			(_uint)_width * 4,
			static_cast<UINT>(frameBuffer.size() * sizeof(uint32_t)),
			reinterpret_cast<BYTE*>(frameBuffer.data()),
			&pWICBitmap
		);
		if (SUCCEEDED(hresult))
		{
			hresult = Management->renderTarget->CreateBitmapFromWicBitmap(
				pWICBitmap.Get(), nullptr, &pBitmap);

			if (SUCCEEDED(hresult))
            {
                _textures.push_back(pBitmap);
				std::cout << _path << "Frame " << frameNumber << " loaded" << std::endl;
				//조금만 애니메이션이 무거워지면 로딩하는데 하루종일 걸리네...
            }
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
