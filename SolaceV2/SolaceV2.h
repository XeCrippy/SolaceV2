#pragma once
#include "stdafx.h"

class PluginMain {

public:
    static void Start();

    static void Stop();

    //static std::string GetPath();

private:
    static bool s_Running;
    static uint32_t s_CurrentTitleId;

    static uint32_t Update(void*);

    static void InitNewTitle(uint32_t newTitleId);
};
