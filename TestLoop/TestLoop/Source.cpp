#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


int main() 
{
  unsigned waitTime = 100;
  char outputString[128] = "Test Line\n";
  while (true)
  {
    std::cout << outputString;
    Sleep(100);
  }
  return 0;
}