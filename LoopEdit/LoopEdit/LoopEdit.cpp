#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <memoryapi.h>
#include <psapi.h>
#include <string>
  

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
  bPrintProcesses = false;
  DWORD pid = GetPID();
  HANDLE hTargetProcessToken = OpenProcess(WRITE_DAC | READ_CONTROL | PROCESS_VM_READ, false, pid);
  std::string mm;
  LPSTR pBuffer[128];
  pBuffer = mm;

  DWORD FileName = GetProcessImageFileNameA(hTargetProcessToken, *pBuffer, 0x00FF);


  std::cout << &hTargetProcessToken << std::endl;
  std::cout << hTargetProcessToken << std::endl;
  hTargetProcessToken;
  
  
  CloseHandle(hTargetProcessToken);
  std::cin.ignore();
  return 0;
}
