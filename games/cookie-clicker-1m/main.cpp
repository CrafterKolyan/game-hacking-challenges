#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>
#include <functional>

#include <conio.h>
#include <windows.h>

constexpr std::chrono::milliseconds default_delay = std::chrono::milliseconds(10);
constexpr int SYMBOLS_IN_LINE = 80;
std::mutex output_mutex;

typedef std::pair<std::pair<std::string, std::string>, std::pair<int, int>> factory_upgrade;

class Timer {
public:
  Timer(std::function<void ()> callback,
        std::chrono::milliseconds delay = std::chrono::milliseconds(1000),
        bool repeat = false) : _callback(callback), _delay(delay), _repeat(repeat) {

  }
  void start(bool asynchronous = true) {
    if (asynchronous) {
      std::thread([&]() {
        do {
          std::this_thread::sleep_for(_delay);
          _callback();
        } while(_repeat);
      }).detach();
    } else {
      do {
        std::this_thread::sleep_for(_delay);
        _callback();
      } while(_repeat);
    }
  }

  void setRepeat(bool repeat) {
    _repeat = repeat;
  }

private:
  std::function<void ()> _callback;
  std::chrono::milliseconds _delay;
  bool _repeat;
};

int getch_noblock() {
    if (_kbhit())
        return _getch();
    else
        return -1;
}

void clear_current_line() {
  std::cout << std::string(SYMBOLS_IN_LINE, ' ') << "\r";
  std::cout.flush();
}

void add_cookies(int &total_cookies, int &remainder, int production_rate, int capacity, std::chrono::milliseconds delay) {
  constexpr int MILLISECONDS_IN_SECONDS = std::chrono::seconds(1) / std::chrono::milliseconds(1);
  int current_remainder = production_rate * delay.count() % MILLISECONDS_IN_SECONDS;
  remainder += current_remainder;
  if (remainder >= MILLISECONDS_IN_SECONDS) {
    ++total_cookies;
    remainder -= MILLISECONDS_IN_SECONDS;
  }
  total_cookies += production_rate * delay.count() / MILLISECONDS_IN_SECONDS;
  total_cookies = std::min(total_cookies, capacity);
  if (total_cookies == capacity) {
    remainder = 0;
  }
}

void buy_storage_upgrade(int &total_cookies, int &capacity, size_t &current_storage_upgrade, std::vector<std::pair<int, int>> &storage_upgrades) {
  if (current_storage_upgrade >= storage_upgrades.size()) {
    std::cout << "You bought all storage upgrades" << std::endl;
    return;
  }
  std::pair<int, int> storage_upgrade = storage_upgrades[current_storage_upgrade];
  if (total_cookies < storage_upgrade.first) {
    std::cout << "Not enough money to buy storage upgrade." << std::endl;
    return;
  }
  total_cookies -= storage_upgrade.first;
  capacity = storage_upgrade.second;
  ++current_storage_upgrade;
}

void buy_factory_upgrade(int &total_cookies,
                         int &production_rate,
                         factory_upgrade &factory_upgrade) {
  int price = factory_upgrade.second.first;
  if (total_cookies < price) {
    std::cout << "Not enough money to buy " << factory_upgrade.first.first << "." << std::endl;
    return;
  }
  total_cookies -= price;
  production_rate += factory_upgrade.second.second;
  factory_upgrade.second.first = price * 11 / 10;
}

int main() {
  auto start_time = std::chrono::steady_clock::now().time_since_epoch();

  std::ios_base::sync_with_stdio(false);
  int total_cookies = 0;
  int remainder = 0;
  int production_rate = 1;
  int capacity = 10;

  size_t current_storage_upgrade = 0;
  std::vector<std::pair<int, int>> storage_upgrades = {
    {10, 25},
    {20, 50},
    {45, 100},
    {99, 250},
    {200, 500},
    {499, 777},
    {667, 1000},
    {900, 2000},
    {1750, 3000},
    {2250, 5000},
    {3750, 7500},
    {6650, 10000},
    {9001, 15000},
    {14444, 25000},
    {20000, 50000},
    {49999, 100000},
    {98000, 250000},
    {200000, 350000},
    {300000, 500000},
    {450000, 750000},
    {600000, 900000},
    {800000, 1000000}
  };
  std::vector<factory_upgrade> factory_upgrades = {
    {{"Worker", "w"}, {10, 1}},
    {{"Specialist", "s"}, {250, 10}},
    {{"Professional", "p"}, {10000, 500}},
    {{"Machine", "m"}, {200000, 10000}},
  };

  std::unordered_map<std::string, std::function<void()>> commands = {
    { "c", [&](){buy_storage_upgrade(total_cookies, capacity, current_storage_upgrade, storage_upgrades);} },
  };

  for (auto &u : factory_upgrades) {
    commands[u.first.second] = [&](){buy_factory_upgrade(total_cookies, production_rate, u);};
  }

  Timer timer = Timer([&total_cookies, &remainder, &production_rate, &capacity](){
    add_cookies(total_cookies, remainder, production_rate, capacity, default_delay);
  }, default_delay, true);
  timer.start(true);

  HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO screenInfo;
  GetConsoleScreenBufferInfo(consoleWindow, &screenInfo);
  SetConsoleMode(consoleWindow, ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS);

  Timer timer_print = Timer([&]() {
    std::lock_guard<std::mutex> lock(output_mutex);
    SetConsoleCursorPosition(consoleWindow, screenInfo.dwCursorPosition);
    clear_current_line();
    SetConsoleCursorPosition(consoleWindow, screenInfo.dwCursorPosition);
    std::cout << "Total cookies: " << total_cookies << " Capacity: " << capacity << " Production rate: " << production_rate << std::endl << std::endl;

    std::cout << "Upgrades:" << std::endl;
    if (current_storage_upgrade < storage_upgrades.size()) {
      std::pair<int, int> storage_upgrade = storage_upgrades[current_storage_upgrade];
      std::cout << "Storage: " << "Cost: " << storage_upgrade.first << " c" << " New capacity: " << storage_upgrade.second << " c" << " (command: 'c')" << std::endl;
    }
    for (const auto &u : factory_upgrades) {
      std::cout << u.first.first << ": Cost: " << u.second.first << " c Production rate: " << u.second.second << " c/s (command: '" << u.first.second << "')" << std::endl;
    }
    std::cout.flush();
  }, default_delay, true);
  timer_print.start(true);

  std::string input;
  while (total_cookies != storage_upgrades.back().second) {
    input = getch_noblock();
    std::lock_guard<std::mutex> lock(output_mutex);

    if (input[0] != -1) {
      clear_current_line();
    }
    auto command = commands.find(input);
    if (command != commands.end()) {
      command->second();
    }
  }
  auto end_time = std::chrono::steady_clock::now().time_since_epoch();
  double score = 60000 * std::chrono::seconds(1) / (end_time - start_time);
  std::lock_guard<std::mutex> lock(output_mutex);
  clear_current_line();
  std::cout << std::endl;
  std::cout << "Score: " << score << " Time: " << (end_time - start_time) / std::chrono::seconds(1) << " s" << std::endl;
}
