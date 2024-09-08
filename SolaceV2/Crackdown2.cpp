#include "stdafx.h"
#include "Crackdown2.h"

namespace SolaceV2 {

	uint32_t Crackdown2::apocalypse = 0x82719790;
	uint32_t Crackdown2::consoleCmds = 0x82771EB0;

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
		Page2 += newLine + newLine;
		Page2 += L"[*] This is just a sample.";
		return Page2.c_str();
	}

	//static void (*Crackdown2::Apocalypse)(); //= reinterpret_cast<void(*)()> (Crackdown2::apocalypse);
	
	void Crackdown2::FlyMode() {
		ConsoleCmd("fly");
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
		//CrackdownTU6StaticCheats();
		MessageBox();

		while (Utilities::Xam::GetCurrentTitleId() == Utilities::Games::GAME_CRACKDOWN2) {

			bool hasToggled = false;
			XInputGetState(0, &state);

			if (XInputGetState(0, &state) == ERROR_SUCCESS) {

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {

					MessageBox();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_X) {

					//Outlines();
					Apocalypse();
					hasToggled = true;
				}

				if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

					FlyMode();
					hasToggled = true;
				}
			}
			if (hasToggled) Sleep(500);
		}
	}
}