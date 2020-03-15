#include <iostream>

#include <memoryapi.h>
#include <handleapi.h>
#include <processthreadsapi.h>
#include <tlhelp32.h>

constexpr char applicationName[] = "cookie-clicker-1m.exe";
constexpr DWORD_PTR valueAddress = 0x0061FAC8; // Found using Cheat Engine 6.8.3
constexpr int PRODUCTION_RATE_VALUE = 999999999;

DWORD find_process_id(const char *applicationName) {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 entry;
  entry.dwSize = sizeof(PROCESSENTRY32);

  while (Process32Next(snapshot, &entry)) {
    if (strcmp(entry.szExeFile, applicationName) == 0) {
      CloseHandle(snapshot);
      return entry.th32ProcessID;
    }
  }
  CloseHandle(snapshot);
  return -1;
}
 
int main() {
  DWORD game_pid = find_process_id(applicationName);
  HANDLE game_process = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, game_pid);

  if (game_process == nullptr) {
    std::cout << "Start " << applicationName << " first" << std::endl;
    return 1;
  }

  int value = PRODUCTION_RATE_VALUE;
  if (!WriteProcessMemory(game_process, (LPVOID)valueAddress, &value, sizeof(value), nullptr)) {
    std::cout << "Can't write to memory of process " << applicationName << std::endl;
    return 1;
  }
  std::cout << "HACKED " << applicationName << "! Production rate now is " << value << std::endl;
}
