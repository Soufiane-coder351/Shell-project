#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  std::cout << "$ ";
  while(true){
  
    std::string userCommand;
    std::getline(std::cin, userCommand);
  
    if(userCommand == "exit") break;

    std::cout << userCommand << ": command not found" << std::endl;
    std::cout << "$ ";
  }

}
