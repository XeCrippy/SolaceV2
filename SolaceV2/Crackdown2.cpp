#include "stdafx.h"
#include "Crackdown2.h"

namespace SolaceV2 {
	bool Crackdown2::showFps = false;

	uint32_t Crackdown2::apocalypse = 0x82719790;
	uint32_t Crackdown2::consoleCmds = 0x82771EB0;
	uint32_t Crackdown2::showfps = 0x83801B0C;

	uint32_t Crackdown2::fps_on = 1;

	void(*Crackdown2::Apocalypse)()= reinterpret_cast<void(*)()> (Crackdown2::apocalypse);
	void(*Crackdown2::ConsoleCmd)(std::string command) = reinterpret_cast<void(*)(std::string command)> (0x82771EB0);

	const wchar_t* buttonLabels[] = { L"Continue" };
	const wchar_t* Title = L"Crackdown 2 TU5 Trainer";

	const wchar_t* MainPage() {
		std::wstring newLine = L"\r\n";
		std::wstring Page2;
		Page2 += L"Fly Mode = DPAD_LEFT+A";
		Page2 += newLine;
		Page2 += L"Apacolypse = DPAD_LEFT+X";
		Page2 += newLine;
		Page2 += L"Show FPS = DPAD_LEFT+Y";
		Page2 += newLine + newLine;
		Page2 += L"[*] This is just a sample.";
		return Page2.c_str();
	}
	
	void Crackdown2::FlyMode() {
		ConsoleCmd("fly");
	}

	bool Crackdown2::ShowFPS() {
		if (!Crackdown2::showFps) {
			Utilities::Memory::WriteUInt32(Crackdown2::showfps, 1);
			Crackdown2::showFps = true;
		}
		else {
			Utilities::Memory::WriteUInt32(Crackdown2::showfps, 0);
			Crackdown2::showFps = false;
		}
		return Crackdown2::showFps;
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
					ShowFPS();
					hasToggled = true;
				}
			}
			if (hasToggled) Sleep(300);
		}
	}
}