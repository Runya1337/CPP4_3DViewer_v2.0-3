#include <cctype>  // Для isdigit
#include <iostream>
#include <string>

class Parser {
 public:
  bool IsDigit(const std::string& lex) {
    bool status = true;
    int counter_index = 0;
    int counter_dot = 0;
    if (lex[0] == '-') {
      counter_index++;
    }
    for (; counter_index < lex.size(); counter_index++) {
      if (isdigit(lex[counter_index])) {
        continue;
      } else if (lex[counter_index] == '.' && counter_dot == 0) {
        counter_dot++;
      } else {
        std::cout << "\nНе число подается\n\n";
        status = false;
        break;
      }
    }
    if (counter_dot > 1) {
      std::cout
          << "\nПодается некорректное число с большим количеством точек\n\n";
      status = false;
    }
    return status;
  }
};

int main() {
  Parser parser;
  std::string input;
  std::cout << "Введите строку для проверки: ";
  std::getline(std::cin, input);
  bool result = parser.IsDigit(input);
  if (result) {
    std::cout << "Строка является числом." << std::endl;
  } else {
    std::cout << "Строка не является числом." << std::endl;
  }
  return 0;
}
