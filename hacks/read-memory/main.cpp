#include <iostream>

#include <memoryapi.h>
#include <handleapi.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>

constexpr char applicationName[] = "guess-the-number.exe";
constexpr DWORD_PTR valueAddress = 0x0061F2A8; // Found using Cheat Engine 6.8.3

HANDLE find_process(const char *applicationName) {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);

  HANDLE process = nullptr;
  while (Process32Next(snapshot, &entry)) {
    if (strcmp(entry.szExeFile, applicationName) == 0) {
      process = OpenProcess(PROCESS_VM_READ, FALSE, entry.th32ProcessID);
      break;
    }
  }
  CloseHandle(snapshot);

  return process;
}
 
int main() {
  HANDLE game_process = find_process(applicationName);

  if (game_process == nullptr) {
    std::cout << "Start " << applicationName << " first" << std::endl;
    return 1;
  }

  long long value;
  if (!ReadProcessMemory(game_process, (LPCVOID)valueAddress, &value, sizeof(value), nullptr)) {
    std::cout << "Can't read memory of process " << applicationName << std::endl;
    return 1;
  }
  std::cout << "Number to guess: " << value << std::endl;
}
