#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <memoryapi.h>
#include <psapi.h>
#include <string>
  

bool bPrintProcesses;


HANDLE GetHandle(DWORD pid) 
{
    return OpenProcess(WRITE_DAC | READ_CONTROL | PROCESS_VM_READ, false, pid);
}


HMODULE GetModule(DWORD pid)
{
    HMODULE hMods[1024];
    HANDLE pHandle = GetHandle(pid);
    DWORD cbNeeded;
    unsigned int i;

    if (EnumProcessModules(pHandle, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(pHandle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
            {
                std::wstring wstrModName = szModName;
                std::wstring wstrModContain = L"TestLoop.exe";
                if (wstrModName.find(wstrModContain) != std::string::npos)
                {
                    CloseHandle(pHandle);
                    return hMods[i];
                }
            }
        }
    }
    return nullptr;
}

DWORD GetPID() 
{
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

  if (Process32First(snapshot, &entry) == TRUE) 
  {
    while (Process32Next(snapshot, &entry) == TRUE)
    {
      if (bPrintProcesses)
      {
        std::wcout << entry.szExeFile << "  " << entry.th32ProcessID << std::endl;
      }
      if (_wcsicmp(entry.szExeFile, L"TestLoop.exe") == 0)
      {
        return entry.th32ProcessID;
      }
    }
  }
  return 0x00000000;
}

int main()
{
  bPrintProcesses = false;
  DWORD pid = GetPID();
  //wchar_t pBuffer[128];
  //wchar_t bufferLocation = &pBuffer;

  HMODULE Module = GetModule(pid);
  DWORD BaseAddress = (DWORD)Module;
  std::cout << BaseAddress << "\n";

  // DWORD FileName = GetProcessImageFileNameA(hTargetProcessToken, bufferLocation, 0x00FF);

  std::cin.ignore();
  return 0;
}
