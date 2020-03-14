#include <iostream>
#include <string>

int request_int(std::string prompt_string = "") {
  std::cout << prompt_string;
  int x;
  std::cin >> x;
  return x;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int maximum_number = request_int("Type maximum possible number: ");
  std::cout << maximum_number << std::endl;
}
