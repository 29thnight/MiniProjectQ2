#include <ClientWorld.h>
#include <ClientLevel.h>
#include <TestActor.h>
#include <TimeManager.h>
#include <SoundManager.h>
#include <Level.h>

bool Client::ClientWorld::BeginPlay()
{
	AddLevel<ClientLevel>();

	Sound->PlaySound("NotAHero", CHANNEL_BGM, LOOP_ONCE);
	Sound->SetVolume(CHANNEL_BGM, 1.f);

	std::cout << "SoundPos : " << Sound->GetPosition(CHANNEL_BGM) << std::endl;
	std::cout << "SoundLength : " << Sound->GetLength(CHANNEL_BGM) << std::endl;

	SettingCamera();
	SettingTrackingCameraTarget(FindActor("TestActor"));

	return isBeginPlayEnd;
}

void Client::ClientWorld::Tick(_duration deltaSeconds)
{
	static float elapsedTime = 0.f;
	elapsedTime += Time->DurationToFloat(deltaSeconds);

	if (elapsedTime > 1.f)
	{
		std::cout << "FPS : " << Time->GetFPS() << " ";
		std::cout << "SoundPos : " << Sound->GetPosition(CHANNEL_BGM) << std::endl; 
		elapsedTime = 0.f;
	}

	Super::Tick(deltaSeconds);
}

Client::ClientWorld* Client::ClientWorld::Create()
{
	return new ClientWorld();
}

void Client::ClientWorld::Destroy()
{
	Super::Destroy();
}
