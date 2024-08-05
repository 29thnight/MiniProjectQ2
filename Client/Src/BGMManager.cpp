#include <BGMManager.h>
#include <SoundManager.h>
#include "../../ThirdParty/nlohmann/json.hpp"

void Client::BGMManager::BeginPlay()
{
	Super::BeginPlay();

	//BGM 리스트를 불러온다.
	nlohmann::json json;
	std::ifstream bgmFiles("BGMList.json");
	json << bgmFiles;

	if(json.contains("StageNumber"))
	if(json.contains("Stage1"))
	{
		json["Stage1"].get_to(_bgmList);
	}

}

void Client::BGMManager::Tick(_duration deltaSeconds)
{
}

void Client::BGMManager::Fixed()
{
}

void Client::BGMManager::EndPlay()
{
}
