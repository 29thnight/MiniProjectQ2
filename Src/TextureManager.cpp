#include <CoreDefine.h>
#include <Texture.h>
#include <CoreManager.h>
#include <TextureManager.h>

namespace file = std::filesystem;

bool Engine::TextureManager::LoadTexture(LPCWSTR filePath)
{
    file::path rootPath(filePath);

    for (const auto& entry : file::directory_iterator(rootPath))
    {
        if (entry.is_directory())
        {
            if (entry.path().filename() == "." || entry.path().filename() == "..")
                continue;

            LoadTexture(entry.path().wstring().c_str());
        }
        else
        {
            file::path fullPath = entry.path();

            std::wstring tag = fullPath.parent_path().wstring();
			tag = tag.substr(tag.find_last_of(L"/") + 1);
			std::replace(tag.begin(), tag.end(), L'\\', L'/');

            Texture* pTexture = _textures[tag].Get();

            if (nullptr == pTexture)
            {
                pTexture = Texture::Create();
                pTexture->LoadTexture(fullPath.wstring().c_str());
                _textures[tag] = pTexture;
            }
            else
            {
                pTexture->LoadTexture(fullPath.wstring().c_str());
            }
        }
    }

    return true;
}

Engine::Texture* Engine::TextureManager::FindTexture(_pwstring fileTag)
{
    return _textures[fileTag].Get();
}

void Engine::TextureManager::Destroy()
{
	_textures.clear();
}
