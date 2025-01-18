
#include<iostream>
#include<random>
#include<array>
#include<cmath>
using namespace std;
array<int, 5> game1(array<int, 5>& list, int tok) {
	default_random_engine eng(static_cast<unsigned int>(time(0)));
	if (tok > 5) {
		for (int i = 0; i < 4; i++) {
			uniform_int_distribution <unsigned int> randInt(1, tok - 5 + i);
			list[i] = randInt(eng);
			tok -= list[i];

		}
		list[4] = tok;
	}
	else if (tok == 5)
		list = { 1,1,1,1,1 };
	return list;
}


int* game2(int size) {
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		double g = 10 * exp(-pow(i + 1 - 5, 2) / 10.89);
		arr[i] = static_cast<int>(round(g));
	}
	return arr;
}

array<int, 5> game1_1(array<int, 5>& list, int tok, int turn, string p1, string p2) {
	if (tok <= 0) {
		return list;
	}
	char x = 'A';
	for (int j = 0; j < 5; j++) {
		cout << x << ": ";
		for (int k = 0; k < list[j]; k++)
			cout << "O";
		cout << endl;
		x++;
	}
	if (turn == 1) {
		char rowChoice;
		int numberChoice;
		bool condition = false;
		while(condition==false){
			cout << p1 << " choose a row and the number of token to remove(1 or 2) : ";
			cin >> rowChoice >> numberChoice;
			try
			{
				if ((rowChoice < 65) || (rowChoice > 69)) {
					throw rowChoice;
				}
				else if ((numberChoice < 1 || numberChoice > 2))
					throw numberChoice;
				else if (numberChoice > list[rowChoice - 65])
					throw "no more";
				condition = true;
			}
			catch (char y)
			{
				cout << "Invalid input: The row doesnt exist. Try again.\n" << endl;
			}
			catch (int n) {
				cout<<"Invalid input: You only can remove 1 or 2 chips. Try again.\n" << endl;
			}
			catch (...) {
				cout << "Invalid input: You cannot remove that many from this pile. Try again.\n";
			}

		}
		
		list[rowChoice - 65] -= numberChoice;

		if (list[0] == 0 && list[1] == 0 && list[2] == 0 && list[3] == 0 && list[4] == 0) {
			cout << p1 << " wins!" << endl;
			return list;
		}
		turn = 2;
		return game1_1(list, tok, turn, p1, p2);
	}
	else {
		char rowChoice;
		int numberChoice;
		bool condition3 = false;
		while (condition3 == false) {
			cout << p2 << " choose a row and the number of token to remove(1 or 2) : ";
			cin >> rowChoice >> numberChoice;
			try
			{
				if ((rowChoice < 65) || (rowChoice > 69)) {
					throw rowChoice;
				}
				else if ((numberChoice < 1 || numberChoice > 2))
					throw numberChoice;
				else if (numberChoice > list[rowChoice - 65])
					throw "no more";
				condition3 = true;
			}
			catch (char y)
			{
				cout << "Invalid input: The row doesnt exist. Try again.\n" << endl;
			}
			catch (int n) {
				cout << "Invalid input: You only can remove 1 or 2 chips. Try again.\n" << endl;
			}
			catch (...) {
				cout << "Invalid input: You cannot remove that many from this pile. Try again.\n";
			}
		}
		list[rowChoice - 65] -= numberChoice;
		if (list[0] == 0 && list[1] == 0 && list[2] == 0 && list[3] == 0 && list[4] == 0) {
			cout << p2 << " wins!" << endl;
			return list;
		}
		turn = 1;
		return game1_1(list, tok, turn, p1, p2);
	}
}

int* game2_2(int* arr, int turn, int boardSize, string p1) {
	char rowChoice;
	int numberChoice;
	char x = 'A';
	for (int j = 0; j < boardSize; j++) {
		cout << x << ": ";
		for (int k = 0; k < arr[j]; k++)
			cout << "O";
		cout << endl;
		x++;
	}
	if (turn == 1) {
		bool condition4 = false;
		while (condition4 == false) {
			cout << p1 << " choose a row and the number of token to remove(1 or 2) : ";
			cin >> rowChoice >> numberChoice;
			try
			{
				if ((rowChoice < 65 || rowChoice >(64 + boardSize)))
					throw rowChoice;
				else if ((numberChoice < 1 || numberChoice > 2) || numberChoice > arr[rowChoice - 65])
					throw numberChoice;
				condition4 = true;
			}
			catch (...)
			{
				cout << "Invalid input. Try again." << endl;

			}
		}
		
		arr[rowChoice - 65] -= numberChoice;
		int verif = 0;
		for (int len = 0; len < boardSize; len++) {//condition
			verif += arr[len];
		}
		if (verif == 0) {
			char x = 'A';
			for (int j = 0; j < boardSize; j++) {
				cout << x << ": ";
				for (int k = 0; k < arr[j]; k++)
					cout << "O";
				cout << endl;
				x++;
			}
			cout << p1 << " wins!" << endl;
			return arr;
		}
		turn = 2;
		return game2_2(arr, turn, boardSize, p1);
	}
	else {
		cout << "Computer's turn: \n\n";
		int xorState = 0, biggest = 0;
		for (int index = 0; index < boardSize; index++) {
			xorState ^= arr[index];
			if (arr[index] > biggest) {
				biggest = index;
			}
		}
		rowChoice = biggest + 65;
		if (xorState == 2) {
			numberChoice = 2;
		}
		else
			numberChoice = 1;

		arr[rowChoice - 65] -= numberChoice;//remove choice
		cout << "Computer chooses: " << rowChoice << numberChoice << " \n";
		int verif = 0;
		for (int len = 0; len < boardSize; len++) {//condition
			verif += arr[len];
		}
		if (verif == 0) {
			char x = 'A';
			for (int j = 0; j < boardSize; j++) {
				cout << x << ": ";
				for (int k = 0; k < arr[j]; k++)
					cout << "O";
				cout << endl;
				x++;
			}
			cout << "computer wins!" << endl;
			return arr;
		}
		turn = 1;
		return game2_2(arr, turn, boardSize, p1);
	}
}

int main() {
	array<int, 5> board{};
	int* board2 = nullptr;
	int game_choice, token;
	char rowChoice;
	int numberChoice;
	string user1;
	int turn = 1;
	bool condition1 = false;
	while (condition1 == false) {
		cout << "Choose game mode: \n1) Two players(user vs user)\n2) One player(user vs PC)" << endl;
		cout << "Mode: ";
		cin >> game_choice;
		try
		{
			if ((game_choice != 1) && (game_choice != 2))
				throw game_choice;
			condition1 = true;
		}
		catch (...)
		{
			cout << "Invalid game choice input. Try again.\n";
		}
	}
	if (game_choice == 1) {           //Game 1
		string user2; 
		cout << "Game 1:\n\nEnter name\nUser1: "; cin >> user1;
		cout << "User2: "; cin >> user2;
		bool condition2 = false;
		while (condition2 == false) { 
			cout << "Enter number of token(>=5): "; cin >> token;
			try
			{
				if (token < 5)
					throw token;
				condition2 = true;
			}
			catch (...)
			{
				cout << "Number of token is smaller than five. try again\n";
			}
		}
		game1(board, token);//generates the board
		game1_1(board, token, 1, user1, user2); //the game
	}
	else {           //Game 2
		int boardSize;
		cout << "Game 2: \n\nEnter name:\nUser 1: "; cin >> user1;
		cout << "Enter number of rows(2>r>10): "; cin >> boardSize;  //apres ajoute verifyer
		board2 = game2(boardSize);
		game2_2(board2, 1, boardSize, user1);
	}
}
