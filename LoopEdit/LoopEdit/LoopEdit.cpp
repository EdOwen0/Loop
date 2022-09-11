#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include "processthreadsapi.h"


bool bPrintProcesses;

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
  bPrintProcesses = true;
  DWORD pid = GetPID();
  HANDLE hProcess = OpenProcess(WRITE_DAC | READ_CONTROL, false, pid);
  
  
  std::cout << "Hello World!\n";


  CloseHandle(hProcess);
  return 0;
}
