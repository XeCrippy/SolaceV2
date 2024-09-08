#pragma once
#include "stdafx.h"

namespace SolaceV2 {
	class Crackdown2 {
	public: 
		static void LoadPlugin();

	private:
		//bool outlines = false;
		//bool perfGraphs = false;
		//bool dbgText = false;
		//bool showFps = false;

		//uint8_t _off = 0;
		//uint8_t _on = 1;
		//uint32_t fps_off = 0;
		//uint32_t fps_on = 1;
		//uint32_t outlines_off = 0;
		//uint32_t outlines_on = 2;

		static uint32_t apocalypse;// = 0x82719790;
		static uint32_t consoleCmds;// = 0x82771EB0;
		//uint32_t enableafterlights = 0x830A0545;
		//uint32_t enableoutlines = 0x830A0544;
		//uint32_t enableshadows = 0x830A054F;
		//uint32_t gputiming = 0x83801A00;
		//uint32_t hudopacity = 0x83092608;
		//uint32_t outlinemode = 0x83801164; // dword
		//uint32_t perfgraphs = 0x83801A01;
		//uint32_t redDebugText = 0x83800AEF;
		//uint32_t showfps = 0x83801B0C; // dword
		//uint32_t togglebloom = 0x830A054E;

		//bool DrawOutlines();
		//bool RedDebugText();
		//bool ShowFps();
		//bool ShowGraphs();

		static void (*Crackdown2::Apocalypse)(); //= reinterpret_cast<void(*)()> (Crackdown2::apocalypse);
		static void FlyMode();
		//void GodMode();
		//void InfiniteAmmo();
		//void MaxAgentSkills();
		static void (*Crackdown2::ConsoleCmd)(std::string command);
		//void Suicide();

		static void MessageBox();
	};
}
