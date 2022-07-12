#include <iostream>
#include <conio.h>

int main() {
	int var,win=0,count=0;
	bool check = 1;
	int secret;
	srand(time(0));
	std::cout << "Welcome to the rock/paper/scissors wars vs computer!";
	std::cout  << "rock - 1 \tpaper - 2 \tscissors - 3 \t quit - 4\n";
	do {
		count++;
		std::cout << "Your choice: r/p/s:  ";
		std::cin >> var;
		secret = rand()% 3 + 1;//1-r 2-p 3-s

		if (var == secret) {
			std::cout << "congratulation!\n\n";
			win++;
		}
		else if (var == 4) {
			check = 0; std::cout << "Bye!" << "Win - " << win << " Lose - " << (count-1) - win;
		}
		else {
			std::cout << "you'll definitely win next time :) secret was - ";
			if (secret == 1) std::cout << "rock";
			else secret == 2 ? std::cout << "paper" : std::cout << "scissors";
			std::cout << std::endl<< std::endl;
		}
	} while (check);
	
	return 0;
}
