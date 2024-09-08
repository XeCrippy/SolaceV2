// SolaceV2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SolaceV2.h"

bool PluginMain::s_Running = false;
uint32_t PluginMain::s_CurrentTitleId = 0;

void PluginMain::Start()
{
	s_Running = true;
	Utilities::Memory::ThreadEx(reinterpret_cast<PTHREAD_START_ROUTINE>(Update), nullptr, 2);
}

void PluginMain::Stop()
{
	s_Running = false;
	Sleep(250);
}

uint32_t PluginMain::Update(void*)
{
	while (s_Running)
	{
		uint32_t newTitleId = Utilities::Xam::GetCurrentTitleId();
		if (newTitleId != s_CurrentTitleId)
			InitNewTitle(newTitleId);
	}
	return 0;
}

void PluginMain::InitNewTitle(uint32_t newTitleId)
{
	s_CurrentTitleId = newTitleId;

	switch (newTitleId)
	{
	case Utilities::GAME_DASHBOARD:
		Sleep(3000);
		Dashboard dash;
		dash.Init();
		break;

	case Utilities::GAME_CRACKDOWN2:
		Sleep(15000);
		Utilities::Xam::XNotify("Crackdown cheats loaded! Press LB+RB for info");
		SolaceV2::Crackdown2::LoadPlugin();

	default:
		break;
	}
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, void* pReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		PluginMain::Start();

	if (dwReason == DLL_PROCESS_DETACH)
		PluginMain::Stop();

	return TRUE;
}