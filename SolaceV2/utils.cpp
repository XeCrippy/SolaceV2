#include "stdafx.h"
#include "utils.h"

struct STRING
{
    uint16_t Length;
    uint16_t MaxLength;
    char* Buffer;
};

// Imports from xboxkrnl.exe and xam.xex
extern "C"
{
    DWORD XamGetCurrentTitleId();

    bool MmIsAddressValid(void* pAddress);

    void HalReturnToFirmware(uint32_t powerDownMode);

    void RtlInitAnsiString(STRING* pDestinationString, const char* sourceString);

    HRESULT ObCreateSymbolicLink(STRING* pLinkName, STRING* pDevicePath);

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

namespace SolaceV2 {
    // Create a pointer to XNotifyQueueUI in xam.xex
    typedef void (*XNOTIFYQUEUEUI)(XNOTIFYQUEUEUI_TYPE type, uint32_t userIndex, uint64_t areas, const wchar_t* displayText, void* pContextData);
    static XNOTIFYQUEUEUI XNotifyQueueUI = static_cast<XNOTIFYQUEUEUI>(utils::ResolveFunction("xam.xex", 656));

    std::wstring utils::ToWide(const std::string& narrowString)
    {
        // Create the wide string
        std::wstring wideString;

        // Copy the narrow string into the wide string from start to end
        wideString.assign(narrowString.begin(), narrowString.end());

        return wideString;
    }

    uint32_t utils::GetCurrentTitleId()
    {
        return XamGetCurrentTitleId();
    }

    bool utils::IsAddressValid(void* pAddress)
    {
        return MmIsAddressValid(pAddress);
    }

    void utils::Reboot()
    {
        // Declared in xkelib
        const uint32_t rebootRoutine = 1;

        HalReturnToFirmware(rebootRoutine);
    }

    void* utils::ResolveFunction(const std::string& moduleName, uint32_t ordinal)
    {
        HMODULE hModule = GetModuleHandle(moduleName.c_str());

        return (hModule == NULL) ? NULL : GetProcAddress(hModule, reinterpret_cast<const char*>(ordinal));
    }

    void utils::Thread(PTHREAD_START_ROUTINE pStartAddress, void* pArgs)
    {
        CreateThread(nullptr, 0, pStartAddress, pArgs, 0, nullptr);
    }

    void utils::ThreadEx(PTHREAD_START_ROUTINE pStartAddress, void* pArgs, uint32_t creationFlags)
    {
        ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pArgs, creationFlags);
    }

    float utils::ReadFloat(uint32_t Address) {
        return *(float*)Address;
    }

    uint8_t utils::ReadUInt8(uint32_t Address) {
        return *(uint8_t*)Address;
    }

    uint16_t utils::ReadUInt16(uint32_t Address) {
        return *(uint16_t*)Address;
    }

    uint32_t utils::ReadUInt32(uint32_t Address) {
        return *(uint32_t*)Address;
    }

    uint64_t utils::ReadUInt64(uint32_t Address) {
        return *(uint64_t*)Address;
    }

    uint32_t utils::ShowKeyboard(const wchar_t* title, const wchar_t* description, const wchar_t* defaultText, std::string& result, size_t maxLength, uint32_t keyboardType)
    {
        // maxLength is the amount of characters the keyboard will allow, realMaxLength needs to include the \0 to terminate the string
        size_t realMaxLength = maxLength + 1;
        XOVERLAPPED overlapped = {};

        // Create the buffers
        wchar_t* wideBuffer = new wchar_t[realMaxLength];
        char* buffer = new char[realMaxLength];

        // Zero the buffers
        ZeroMemory(wideBuffer, sizeof(wideBuffer));
        ZeroMemory(buffer, sizeof(buffer));

        // Open the keyboard
        XShowKeyboardUI(
            0,
            keyboardType,
            defaultText,
            title,
            description,
            wideBuffer,
            realMaxLength,
            &overlapped
        );

        // Wait until the keyboard closes
        while (!XHasOverlappedIoCompleted(&overlapped))
            Sleep(100);

        // Get how the keyboard was closed (success, canceled or internal error)
        uint32_t overlappedResult = XGetOverlappedResult(&overlapped, nullptr, TRUE);
        if (overlappedResult == ERROR_SUCCESS)
        {
            // Convert the wide string to a narrow string
            wcstombs_s(nullptr, buffer, realMaxLength, wideBuffer, realMaxLength * sizeof(wchar_t));

            // Populate the out string with the narrow string
            result = buffer;
        }

        // Cleanup
        delete[] wideBuffer;
        delete[] buffer;

        return overlappedResult;
    }

    uint32_t utils::ShowMessageBox(const wchar_t* title, const wchar_t* text, const wchar_t** buttonLabels, size_t numberOfButtons, uint32_t* pButtonPressedIndex, uint32_t messageBoxType, uint32_t focusedButtonIndex)
    {
        MESSAGEBOX_RESULT messageBoxResult = { 0 };
        XOVERLAPPED overlapped = { 0 };

        // Open the message box
        XShowMessageBoxUI(
            0,
            title,
            text,
            numberOfButtons,
            buttonLabels,
            focusedButtonIndex,
            messageBoxType,
            &messageBoxResult,
            &overlapped
        );

        // Wait until the message box closes
        while (!XHasOverlappedIoCompleted(&overlapped))
            Sleep(100);

        // Get how the message box was closed (success, canceled or internal error)
        uint32_t overlappedResult = XGetOverlappedResult(&overlapped, nullptr, TRUE);

        // If the message box was closed by pressing "A" on any of the buttons (so not by pressing "B" or the Xbox button)
        // and if the pressed button is request, write the pressed button at pButtonPressedIndex
        if (overlappedResult == ERROR_SUCCESS && pButtonPressedIndex != nullptr)
            *pButtonPressedIndex = messageBoxResult.dwButtonPressed;

        return overlappedResult;
    }

    void utils::WriteFloat(uint32_t Address, float Value) {
        *(float*)Address = Value;
    }

    void utils::WriteUInt8(uint32_t Address, uint8_t Value) {
        *(uint8_t*)Address = Value;
    }

    void utils::WriteUInt16(uint32_t Address, uint16_t Value) {
        *(uint16_t*)Address = Value;
    }

    void utils::WriteUInt32(uint32_t Address, uint32_t Value) {
        *(uint32_t*)Address = Value;
    }

    void utils::WriteUInt64(uint32_t Address, uint64_t Value) {
        *(uint64_t*)Address = Value;
    }

    void utils::XNotify(const std::string& text, XNOTIFYQUEUEUI_TYPE type)
    {
        XNotifyQueueUI(type, 0, XNOTIFY_SYSTEM, utils::ToWide(text).c_str(), nullptr);
    }

    HRESULT utils::MountHdd()
    {
        // Allow the game to access the entire hard drive.
        // The system only allows executables to access the directory they live in and binds it to
        // the "game:" drive. Nothing else is accessible unless you create a symbolic link.

        STRING linkName = { 0 };
        STRING deviceName = { 0 };
        const char destinationDrive[] = "\\??\\hdd:";
        const char hddDevicePath[] = "\\Device\\Harddisk0\\Partition1\\";

        // Initialize the STRING structs
        RtlInitAnsiString(&linkName, destinationDrive);
        RtlInitAnsiString(&deviceName, hddDevicePath);

        // Bind the root of the hard drive to the "hdd:" drive.
        return ObCreateSymbolicLink(&linkName, &deviceName);
    }

    void utils::PulseController()
    {
        XINPUT_VIBRATION xvib;
        xvib.wLeftMotorSpeed = 50000;
        xvib.wRightMotorSpeed = 50000;

        XInputSetState(0, &xvib);

        Sleep(300);

        xvib.wLeftMotorSpeed = 0;
        xvib.wRightMotorSpeed = 0;

        XInputSetState(0, &xvib);
    }
}