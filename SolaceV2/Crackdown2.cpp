#include "stdafx.h"
#include "Crackdown2.h"

namespace SolaceV2 {
	//bool Crackdown2::showFps = false;

	//uint32_t Crackdown2::apocalypse = 0x82719790;
	//uint32_t Crackdown2::consoleCmds = 0x82771EB0;
	//uint32_t Crackdown2::showfps = 0x83801B0C;

	//uint32_t Crackdown2::fps_on = 1;

	void(*Crackdown2::Apocalypse)()= reinterpret_cast<void(*)()> (Crackdown2::apocalypse);
	void(*Crackdown2::ConsoleCmd)(std::string command) = reinterpret_cast<void(*)(std::string command)> (0x82771EB0);

	const wchar_t* buttonLabels[] = { L"Continue" };
	const wchar_t* Title = L"Crackdown 2 TU5 Trainer";

	const wchar_t* MainPage() {
		std::wstring newLine = L"\r\n";
		std::wstring Page2;
		Page2 += L"Fly Mode = Dpad_Left+A";
		Page2 += newLine;
		Page2 += L"Apacolypse = Dpad_Left+X";
		Page2 += newLine;
		Page2 += L"Show FPS = Dpad_Left+Y";
		Page2 += newLine;
		Page2 += L"Show Graphs = Dpad_Left+B";
		Page2 += newLine;
		Page2 += L"God Mode = Dpad_Down+A";
		Page2 += newLine;
		Page2 += L"Infinite Ammo = Dpad_Down+X";
		Page2 += newLine;
		Page2 += L"Max Skills = Dpad_Down+Y";
		Page2 += newLine;
		Page2 += L"Draw Outlines = Dpad_Down+B";
		Page2 += newLine;
		Page2 += L"Suicide = Dpad_Right+A";
		Page2 += newLine + newLine;
		Page2 += L"[*] This is just a sample.";
		return Page2.c_str();
	}
	
	void Crackdown2::FlyMode() {
		ConsoleCmd("fly");
	}

	void Crackdown2::GodMode() {
		ConsoleCmd("god");
	}

	void Crackdown2::InfiniteAmmo() {
		ConsoleCmd("infiniteammo");
	}

	void Crackdown2::MaxAgentSkills() {
		ConsoleCmd("maxagentskills");
	}

	void Crackdown2::Suicide() {
		ConsoleCmd("suicide");
	}

	bool Crackdown2::DrawOutlines() {
		if (!outlines) {
			Utilities::Memory::WriteUInt8(enableoutlines, _on);
			Utilities::Memory::WriteUInt32(outlinemode, outlines_on);
			outlines = true;
		}
		else {
			Utilities::Memory::WriteUInt8(enableoutlines, _off);
			Utilities::Memory::WriteUInt32(outlinemode, outlines_off);
			outlines = false;	
		}
		return outlines;
	}

	bool Crackdown2::RedDebugText() {
		if (!dbgText) {
			Utilities::Memory::WriteUInt8(redDebugText, _on);
			dbgText = true;
		}
		else {
			Utilities::Memory::WriteUInt8(redDebugText, _off);
			dbgText = false;	
		}
		return dbgText;
	}

	bool Crackdown2::ShowFps() {
		if (!Crackdown2::showFps) {
			Utilities::Memory::WriteUInt32(Crackdown2::showfps, 1);
			Utilities::Memory::WriteUInt8(gputiming, _on);
			Crackdown2::showFps = true;
		}
		else {
			Utilities::Memory::WriteUInt32(Crackdown2::showfps, 0);
			Utilities::Memory::WriteUInt8(gputiming, _off);
			Crackdown2::showFps = false;
		}
		return Crackdown2::showFps;
	}

	bool Crackdown2::ShowGraphs() {
		if (!perfGraphs) {
			Utilities::Memory::WriteUInt8(perfgraphs, _on);
			perfGraphs = true;
		}
		else {
			Utilities::Memory::WriteUInt8(perfgraphs, _off);
			perfGraphs = false;
		}
		return perfGraphs;
	}

	void Crackdown2::MessageBox() {
		Utilities::Xam::ShowMessageBox(
			Title,
			MainPage(),
			buttonLabels,
			ARRAYSIZE(buttonLabels),
			nullptr,
			XMB_ALERTICON
		);
	}

	void Crackdown2::LoadPlugin() {
		XINPUT_STATE state = { 0 };
		ZeroMemory(&state, sizeof(state));

		while (Utilities::Xam::GetCurrentTitleId() == Utilities::Games::GAME_CRACKDOWN2) {

			bool hasToggled = false;
			XInputGetState(0, &state);

			if (XInputGetState(0, &state) == ERROR_SUCCESS) {

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
					MessageBox();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
					Apocalypse();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

					FlyMode();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
					ShowFps();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
					ShowGraphs();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
					GodMode();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
					InfiniteAmmo();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
					MaxAgentSkills();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN && state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
					DrawOutlines();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
					Suicide();
					hasToggled = true;
				}
			}
			if (hasToggled) Sleep(300);
		}
	}
}