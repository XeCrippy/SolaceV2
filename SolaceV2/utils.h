#pragma once
#include "stdafx.h"

namespace SolaceV2 {
    
	class utils {
	public:
		static void XNotify(const std::string& text, XNOTIFYQUEUEUI_TYPE type = XNOTIFYUI_TYPE_PREFERRED_REVIEW);

        // Note: Blocks the current thread while waiting for the user to finish typing.
        static uint32_t ShowKeyboard(const wchar_t* title, const wchar_t* description, const wchar_t* defaultText, std::string& result, size_t maxLength = 512, uint32_t keyboardType = VKBD_DEFAULT);

        // Note: Blocks the current thread while waiting for the user to close the message box.
        static uint32_t ShowMessageBox(const wchar_t* title, const wchar_t* text, const wchar_t** buttonLabels, size_t numberOfButtons, uint32_t* pButtonPressedIndex = nullptr, uint32_t messageBoxType = XMB_ALERTICON, uint32_t focusedButtonIndex = 0);

        static uint32_t GetCurrentTitleId();

        static bool IsAddressValid(void* pAddress);

        static void Reboot();

        static HRESULT MountHdd();

        static void PulseController();

        static void* ResolveFunction(const std::string& moduleName, uint32_t ordinal);

        static void Thread(PTHREAD_START_ROUTINE pStartAddress, void* pArgs = nullptr);

        static void ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void* pArgs, uint32_t creationFlags);

        static float ReadFloat(uint32_t Address);
        static uint8_t ReadUInt8(uint32_t Address);
        static uint16_t ReadUInt16(uint32_t Address);
        static uint32_t ReadUInt32(uint32_t Address);
        static uint64_t ReadUInt64(uint32_t Address);

        static void WriteFloat(uint32_t Address, float Value);
        static void WriteUInt8(uint32_t Address, uint8_t Value);
        static  void WriteUInt16(uint32_t Address, uint16_t Value);
        static void WriteUInt32(uint32_t Address, uint32_t Value);
        static void WriteUInt64(uint32_t Address, uint64_t Value);

        static std::wstring utils::ToWide(const std::string& narrowString);
	};
}
