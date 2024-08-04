#include <ClientEntry.h>
#include <ClientWorld.h>
#include <PrototypeEditerWorld.h>

DEFINE_WWINMAIN_RELEASE("GameSettings.ini");
//rlottie 추가하니까 leak잡히네... 쩝... 개빡치네 ㅋㅋ
//DEFINE_WWINMAIN_DEBUG(0, "GameSettings.ini"); <- 일단 풀지말것.

void Client::ClientEntry::CreateWorld()
{
	_pWorld = ClientWorld::Create();
	//_pWorld = PrototypeEditerWorld::Create();
}
