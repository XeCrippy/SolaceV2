#pragma once
#include "stdafx.h"

namespace SolaceV2 {
	class Crackdown2 {
	public: 
	   void LoadPlugin();

	private:
		bool outlines;
		bool perfGraphs;
		bool dbgText;
	    bool showFps;

		static const uint8_t _off = 0;
		static const uint8_t _on = 1;
		static const uint32_t fps_off = 0;
		static const uint32_t fps_on;
		static const uint32_t outlines_off = 0;
		static const uint32_t outlines_on = 2;

		static const uint32_t apocalypse = 0x82719790;
		static const uint32_t consoleCmds;// = 0x82771EB0;
		static const uint32_t enableafterlights = 0x830A0545;
		static const uint32_t enableoutlines = 0x830A0544;
		static const uint32_t enableshadows = 0x830A054F;
		static const uint32_t gputiming = 0x83801A00;
		static const uint32_t hudopacity = 0x83092608;
		static const uint32_t outlinemode = 0x83801164; // dword
		static const uint32_t perfgraphs = 0x83801A01;
		static const uint32_t redDebugText = 0x83800AEF;
		static const uint32_t showfps = 0x83801B0C; // dword
		static const uint32_t togglebloom = 0x830A054E;

		bool DrawOutlines();
		bool RedDebugText();
		bool ShowFps();
		bool ShowGraphs();

		void FlyMode();
		void GodMode();
		void InfiniteAmmo();
		void MaxAgentSkills();
		void MessageBox();
		void Suicide();

		static void (*Crackdown2::Apocalypse)(); // = reinterpret_cast<void(*)()> (0x82719790);
		static void(*Crackdown2::ConsoleCmd)(std::string command);// = reinterpret_cast<void(*)(std::string command)> (0x82771EB0);
		

		
	};
}
