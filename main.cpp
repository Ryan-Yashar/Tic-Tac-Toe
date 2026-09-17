#include <iostream>
#include <cstring>

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
int main() {
  int myChar[5][5] = {{0x250F, 0x2501, 0x2533, 0x2501, 0x2513}, {0x2503, 0x0020, 0x2503, 0x0020, 0x2503}};
  for (int i=0; i<5; i++) {stylepoints(myChar[1][i]);}
  return 0;
}
