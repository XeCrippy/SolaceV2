#pragma once
#include "stdafx.h"

class Dashboard {
public:
    void Init();

private:
    void ShowMainPage();
    void ShowPage2();

    const wchar_t* MainPage();
    const wchar_t* Page2();
};
