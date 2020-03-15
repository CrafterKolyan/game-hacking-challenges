#include <iostream>

#include <memoryapi.h>
#include <handleapi.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>

constexpr char applicationName[] = "guess-the-number.exe";
constexpr DWORD_PTR valueAddress = 0x0061F2B8;
 
int main() {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);

  HANDLE game_process = nullptr;
  while (Process32Next(snapshot, &entry)) {
    if (strcmp(entry.szExeFile, applicationName) == 0) {
      game_process = OpenProcess(PROCESS_VM_READ, FALSE, entry.th32ProcessID);
    }
  }
  CloseHandle(snapshot);

  if (game_process == nullptr) {
    std::cout << "Start " << applicationName << " first" << std::endl;
    return 1;
  }

  unsigned long long value;
  if (!ReadProcessMemory(game_process, (LPCVOID)valueAddress, &value, sizeof(value), nullptr)) {
    std::cout << "Can't read memory of process " << applicationName << std::endl;
    return 1;
  }
  std::cout << "Number to guess: " << value << std::endl;
}
