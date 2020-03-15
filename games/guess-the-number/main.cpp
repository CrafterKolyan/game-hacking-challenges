#include <iostream>
#include <chrono>
#include <string>
#include <random>

constexpr char maximumNumberRead[] = "Type maximum possible number: ";
constexpr char guessRead[] = "Type your guess: ";
constexpr char scoreString[] = "Score: ";

constexpr char expectedIntegerNumber[] = "Expected: integer number";
constexpr char invalidNumber[] = "Number must be not less than 0";
constexpr char toobigNumber[] = "Too big number";

constexpr char gameStart[] = "Try to guess the number";
constexpr char gameLessValue[] = "< (generated number is less)";
constexpr char gameGreaterValue[] = "> (generated number is greater)";

unsigned long long request_ll(std::string prompt_string = "") {
  std::string s;
  unsigned long long value;
  size_t pos = 0;
  while (true) {
    std::cout << prompt_string;
    getline(std::cin, s);
    try {
      value = std::stoll(s, &pos);
      if (pos != s.size()) {
        std::cout << expectedIntegerNumber << std::endl;
        continue;
      }
      break;
    } catch (std::invalid_argument) {
      std::cout << expectedIntegerNumber << std::endl;
    } catch (std::out_of_range) {
      std::cout << expectedIntegerNumber << std::endl;
    }
  }
  return value;
}

double game(long long maximum_number) {
  std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<long long> distribution(0, maximum_number);
  long long value = distribution(generator);

  std::cout << gameStart << std::endl;
  long long guess = request_ll(guessRead);
  unsigned long long guesses = 1;
  while (guess != value) {
    if (value < guess) {
      std::cout << gameLessValue << std::endl;
    } else {
      std::cout << gameGreaterValue << std::endl;
    }
    guess = request_ll(guessRead);
    ++guesses;
  }

  double divisor = log2(std::max(maximum_number, 2LL));
  double score = (1 - guesses / divisor) * 10;
  // Round to two digits
  score = round(score * 100) / 100;
  return score;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  long long maximum_number = request_ll(maximumNumberRead);
  while(maximum_number <= 0) {
    std::cout << invalidNumber << std::endl;
    maximum_number = request_ll(maximumNumberRead);
  }
  double score = game(maximum_number);
  std::cout << scoreString << score << std::endl;
}
