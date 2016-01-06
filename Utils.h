#pragma once
#include "Main.h"

typedef DWORD PTR;

class CUtils {
public:
	//Current Process Directory
	char szProcessDir[MAX_PATH] = { NULL };

	//InfoBox
	auto InfoBox(const char *Msg) -> void
	{
		MessageBoxA(NULL, Msg, "Info", MB_ICONINFORMATION | MB_OK);
	}


	//ReadProcessMemory
	template<typename T>
	auto RPM(DWORD Address, DWORD Buffer) -> void
	{
		ReadProcessMemory(hProcessHandle, Address, Buffer, sizeof(T), NULL);
	}

	//WriteProcessMemory Wrapper
	template<typename T>
	auto WPM(DWORD Address, DWORD Value) -> void
	{
		WriteProcessMemory(hProcessHandle, Address, Value, sizeof(T), NULL);
	}

	auto deletePtr(PTR *ptr) -> void
	{
		delete[] ptr;
	}

	auto AttachTo(const char *ProcName , DWORD dwRights) -> bool
	{
		ProcessName = ProcName;
		HWND hWnd = FindWindowA(NULL, ProcName);
		
		if (!hWnd)
			return false;

		GetWindowThreadProcessId(hWnd, &PID);

		if (!PID)
			return false;

		hProcessHandle = OpenProcess(dwRights, FALSE, PID);

		if (!hProcessHandle)
			return false;

		addToProcessList(hProcessHandle);

		return true;

	}

	//Result will be saved to Client::szProcessDir
	auto GetCurrentDirectory() -> void
	{
		GetModuleFileNameA((HMODULE)GetCurrentProcess(), (LPSTR)szProcessDir, MAX_PATH);
		for (int i = strlen(szProcessDir); i > 0; i--)
		{
			if (szProcessDir[i] == '\\')
			{
				szProcessDir[i + 1] = 0;
				break;
			}
		}
	}

	auto strcompare(const char* One, const char* Two, bool CaseSensitive) -> int
	{
		#if defined _WIN32 || defined _WIN64
		return CaseSensitive ? strcmp(One, Two) : _stricmp(One, Two);
		#else
		return CaseSensitive ? strcmp(One, Two) : strcasecmp(One, Two);
		#endif
	}

	auto GetModuleInfo(std::uint32_t ProcessID, const char* ModuleName) -> MODULEENTRY32
	{
		void* hSnap = nullptr;
		MODULEENTRY32 Mod32 = { 0 };

		if ((hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID)) == INVALID_HANDLE_VALUE)
			return Mod32;

		Mod32.dwSize = sizeof(MODULEENTRY32);
		while (Module32Next(hSnap, &Mod32))
		{
			if (!strcompare(ModuleName, Mod32.szModule, false))
			{
				CloseHandle(hSnap);
				return Mod32;
			}
		}

		CloseHandle(hSnap);
		return{ 0 };
	}

	auto GetTargetProcessModuleInformation(const char *moduleName) -> MODULEENTRY32
	{
		DWORD PID = NULL;
		GetWindowThreadProcessId(FindWindowA(NULL, "Counter-Strike: Global Offensive"), &PID);
		return GetModuleInfo(PID, moduleName);
	}

	DWORD PID = NULL;
	const char *ProcessName = NULL;
	HANDLE hProcessHandle = NULL;
	std::vector<HANDLE>hProcessList;

private:
	auto addToProcessList(HANDLE hProc) -> void
	{
		hProcessList.push_back(hProc);
	}

};