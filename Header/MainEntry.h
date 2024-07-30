#pragma once

#include <SDKDDKVer.h>
#include <windows.h>
#include <CoreDefine.h>

#define DEFINE_WWINMAIN(GAME_SETTINGS_PATH) \
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, \
	_In_opt_ HINSTANCE hPrevInstance, \
	_In_ LPWSTR lpszCmdParam, \
	_In_ int nCmdShow) \
{ \
	\
	_CrtSetBreakAlloc(0); \
	\
	UNREFERENCED_PARAMETER(hPrevInstance); \
	UNREFERENCED_PARAMETER(lpszCmdParam); \
	\
	Client::ClientEntry winApp; \
	\
	winApp.CreateWorld(); \
	\
    Engine::GameSettings gameSetting{}; \
    \
    gameSetting.hInstance = hInstance; \
	gameSetting.pWorld = winApp.ContainWorld(); \
	winApp.LoadGameSettings(GAME_SETTINGS_PATH, gameSetting); \
	EngineInititalize(winApp, gameSetting); \
	\
	_CrtDumpMemoryLeaks(); \
	\
	return EXIT_SUCCESS; \
}

namespace Engine
{
	class World;
	class System;
	class MainEntry abstract
	{
	public:
		MainEntry() = default;
		virtual ~MainEntry() = default;

	public:
		virtual void CreateWorld() abstract; //클라이언트에서 월드의 생성을 강제하기 위한 함수
		World* ContainWorld() const { return _pWorld; }

		bool LoadGameSettings(const std::string& iniPath, GameSettings& settings);
		void Initialize(GameSettings gameSettings);
		void MainLoop();
		void Terminate();

		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	protected:
		World* _pWorld{ nullptr };

	private:
		System* _pSystem{ nullptr };
	};
}