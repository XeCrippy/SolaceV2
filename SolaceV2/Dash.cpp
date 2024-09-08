#include "stdafx.h"

XINPUT_STATE state;

const wchar_t* Dashboard::MainPage() {
    std::wstring newLine = L"\r\n";
    std::wstring mainPage;
    mainPage += L"Sample Welcome Page....";

    return mainPage.c_str();
}



const wchar_t* Dashboard::Page2() {
    std::wstring newLine = L"\r\n";
    std::wstring page2;
    page2 += L"Sample Page 2....";
    page2 += newLine + newLine;
    page2 += L"Author : XeCrippy";
    return page2.c_str();
}

void Dashboard::ShowPage2() {
    const wchar_t* buttonLabels[] = { L"Back", L"Close" };
    uint32_t buttonPressedIndex = 0;

    uint32_t result = Utilities::Xam::ShowMessageBox(
        L"Solace V2 Multi-Game Plugin",
        Page2(),
        buttonLabels,
        ARRAYSIZE(buttonLabels),
        &buttonPressedIndex,
        XMB_ALERTICON
    );

    if (result == ERROR_SUCCESS) {

        switch (buttonPressedIndex) {
        case 0:
            Dashboard::ShowMainPage();
            break;
        case 1:
            break;
        default:
            break;
        }
    }
}

void Dashboard::ShowMainPage() {

    const wchar_t* buttonLabels[] = { L"Next", L"Reboot Console", L"Close" };
    uint32_t buttonPressedIndex = 0;
    uint32_t result = Utilities::Xam::ShowMessageBox(
        L"Solace V2 Multi-Game Plugin",
        MainPage(),
        buttonLabels,
        ARRAYSIZE(buttonLabels),
        &buttonPressedIndex,
        XMB_ALERTICON
    );

    if (result == ERROR_SUCCESS) {

        switch (buttonPressedIndex) {
        case 0:
            Dashboard::ShowPage2();
            break;
        case 1:
            Utilities::Xam::Reboot();
            break;
        default:
            break;
        }
    }
}

void Dashboard::Init()
{
    Utilities::Xam::XNotify("Solace V2 : Dashboard Loaded. Press LB+RB to view info");

    while (Utilities::Xam::GetCurrentTitleId() == Utilities::GAME_DASHBOARD) {

        XInputGetState(0, &state);
        bool hasToggled = false;

        if (XInputGetState(0, &state) == ERROR_SUCCESS) {

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER && state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {

                ShowMainPage();
                hasToggled = true;
            }
        }
        if (hasToggled) Sleep(250);
    }
}