#include <ClientEntry.h>
#include <ClientWorld.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

DEFINE_WWINMAIN_RELEASE("GameSettings.ini");
//rlottie 추가하니까 leak잡히네... 쩝... 개빡치네 ㅋㅋ
//DEFINE_WWINMAIN_DEBUG(1448, "GameSettings.ini"); //<- 일단 풀지말것.

void Client::ClientEntry::CreateWorld()
{
	_pWorld = ClientWorld::Create();
}
