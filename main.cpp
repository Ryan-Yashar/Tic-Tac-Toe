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
  char letter[2] = {'X', 'O'};
  int gameBoard[7][8] = {{0x250F, 0x2501, 0x2533, 0x2501, 0x2533, 0x2501, 0x2513, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2523, 0x2501, 0x254B, 0x2501, 0x254B, 0x2501, 0x252B, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2523, 0x2501, 0x254B, 0x2501, 0x254B, 0x2501, 0x252B, '\n'}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503, 0x0020, 0x2503, '\n'}, {0x2517, 0x2501, 0x253B, 0x2501, 0x253B, 0x2501, 0x251B, '\n'}};
  char userInput[4];
  //Game loop here
  int turns = 0;
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
        return player;
      }
      if (gameBoard[1][i] == letter[player] && gameBoard[3][i] == letter[player] && gameBoard[5][i] == letter[player]) {
        return player;
      }
    }
    if ((gameBoard[1][1] == letter[player] && gameBoard[3][3] == letter[player] && gameBoard[5][5] == letter[player]) || (gameBoard[5][1] == letter[player] && gameBoard[3][3] == letter[player] && gameBoard [1][5] == letter[player])) {
      return player;
    }
    player = (player+1)%2;
    if (player == 0) {
      turns++;
    }
  }
  return 2;
}
int main() {
  cout << vsPlayer()+1;
  cout << " wins!";
  return 0;
}
