#include "stdafx.h"


// Import from xboxkrnl.exe
extern "C"
{
    DWORD __stdcall ExCreateThread(
        HANDLE* pHandle,
        DWORD dwStackSize,
        DWORD* pThreadId,
        void* apiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void* pParameter,
        DWORD dwCreationFlagsMod
    );
}

namespace Utilities {

    void* Memory::ResolveFunction(const std::string& moduleName, uint32_t ordinal)
    {
        HMODULE hModule = GetModuleHandle(moduleName.c_str());

        return (hModule == NULL) ? NULL : GetProcAddress(hModule, reinterpret_cast<const char*>(ordinal));
    }

    void Memory::Thread(PTHREAD_START_ROUTINE pStartAddress, void* pArgs)
    {
        CreateThread(nullptr, 0, pStartAddress, pArgs, 0, nullptr);
    }

    void Memory::ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void* pArgs, uint32_t creationFlags)
    {
        ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pArgs, creationFlags);
    }

    float Memory::ReadFloat(uint32_t Address) {
        return *(float*)Address;
    }

    uint8_t Memory::ReadUInt8(uint32_t Address) {
        return *(uint8_t*)Address;
    }

    uint16_t Memory::ReadUInt16(uint32_t Address) {
        return *(uint16_t*)Address;
    }

    uint32_t Memory::ReadUInt32(uint32_t Address) {
        return *(uint32_t*)Address;
    }

    uint64_t Memory::ReadUInt64(uint32_t Address) {
        return *(uint64_t*)Address;
    }

    void Memory::WriteFloat(uint32_t Address, float Value) {
        *(float*)Address = Value;
    }

    void Memory::WriteUInt8(uint32_t Address, uint8_t Value) {
        *(uint8_t*)Address = Value;
    }

    void Memory::WriteUInt16(uint32_t Address, uint16_t Value) {
        *(uint16_t*)Address = Value;
    }

    void Memory::WriteUInt32(uint32_t Address, uint32_t Value) {
        *(uint32_t*)Address = Value;
    }

    void Memory::WriteUInt64(uint32_t Address, uint64_t Value) {
        *(uint64_t*)Address = Value;
    }
}