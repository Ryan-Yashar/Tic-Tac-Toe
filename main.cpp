#include <iostream>
#include <cstring>
#include <limits>

using namespace std;
//takes 4-digit hexadecimal and prints a utf-16 char (4-digit hexadecimal)
void stylepoints(int myChar) {
  if (myChar > 0x00FF) {
    unsigned char arr[4];
    arr[0] = 0xE0 + (myChar >> 12);
    arr[1] = 0x80 + ((myChar >> 6) & 0x003F);
    arr[2] = 0x80 + (myChar & 0x003F);
    arr[3] = '\0';
    cout << arr;
  } else {
    cout << (char)myChar;
  }
}
int vsPlayer() {
  int player = 0;
  int winner = 0; //this is not zero-indexed, to allow for checking as a boolean win condition as well as reading as a value
  char letter[2] = {'X', 'O'};
  int gameBoard[7][8] = {{0x250F, 0x2501, 0x2533, 0x2501, 0x2533, 0x2501, 0x2513, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2523, 0x2501, 0x254B, 0x2501, 0x254B, 0x2501, 0x252B, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2523, 0x2501, 0x254B, 0x2501, 0x254B, 0x2501, 0x252B, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2517, 0x2501, 0x253B, 0x2501, 0x253B, 0x2501, 0x251B, '\n'}};
  char userInput[4];
  //Game loop here
  int turns = 1;
  cout << "Turn 1\n";
  while (!(turns == 5 && player == 1)) {
    cout << "Player ";
    cout << (char)(player+'1');
    cout << " turn\n\n";
    for (int i=0; i<7; i++) {for (int j=0; j<8; j++) {stylepoints(gameBoard[i][j]);}}
    while (true) {
      cout << "Enter the position you'd like to place an ";
      cout << letter[player];
      cout << ", using format a,b (no space): ";
      cin.get(userInput, 4);
      if ((userInput[1] != ',' || userInput[3] != '\0') || (gameBoard[2*(userInput[0]-'0')-1][2*(userInput[2]-'0')-1] != 0x0020) || ((userInput[0]-'0' < 1 || userInput[0]-'0' > 3) || (userInput[2]-'0' < 1 || userInput[2]-'0' > 3))) {
        cout << "Invalid input. Try again.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        gameBoard[2*(userInput[0]-'0')-1][2*(userInput[2]-'0')-1] = letter[player];
        break;
      }
    }
    for (int i=1; i<6; i += 2) {
      if (gameBoard[i][1] == letter[player] && gameBoard[i][3] == letter[player] && gameBoard[i][5] == letter[player]) {
        winner = player+1;
      }
      if (gameBoard[1][i] == letter[player] && gameBoard[3][i] == letter[player] && gameBoard[5][i] == letter[player]) {
        winner = player+1;
      }
    }
    if ((gameBoard[1][1] == letter[player] && gameBoard[3][3] == letter[player] && gameBoard[5][5] == letter[player]) || (gameBoard[5][1] == letter[player] && gameBoard[3][3] == letter[player] && gameBoard [1][5] == letter[player])) {
      winner = player+1;
    }
    if (winner) {
      cout << letter[winner-1];
      cout << " wins!\n\n";
      for (int i=0; i<7; i++) {for (int j=0; j<8; j++) {stylepoints(gameBoard[i][j]);}}
      cout << '\n';
      return winner;
    }
    if (turns == 5) {
      cout << "Game drawn!\n\n";
      for (int i=0; i<7; i++) {for (int j=0; j<8; j++) {stylepoints(gameBoard[i][j]);}}
      cout << '\n';
      return winner;
    }
    player = (player+1)%2;
    if (player == 0) {
      turns++;
      cout << "Turn ";
      cout << turns;
      cout << '\n';
    }
  }
  return 2;
}
int main() {
  int winner = 0;
  char replay = 'n';
  int wins[2] = {0, 0};
  bool halfflag = false;
  while (true) {
    winner = vsPlayer();
    if (winner == 0) {
      if (halfflag) {
	halfflag = false;
	wins[0] += 1;
	wins[1] += 1;
      } else {
	halfflag = true;
      }
    } else {
      wins[winner-1] += 1;
    }
    cout << "Score is ";
    cout << wins[0];
    if (halfflag) {
      cout << "½";
    }
    cout << " - ";
    cout << wins[1];
    if (halfflag) {
      cout << "½";
    }
    cout << ".\nPlay again? (y/n) ";
    cin.get(replay);
    while ((replay != 'y') && (replay != 'n')) {
      cout << "Input must be 'y' or 'n'. Try again. ";
    }
    if (replay == 'n') {
      break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return 0;
}
