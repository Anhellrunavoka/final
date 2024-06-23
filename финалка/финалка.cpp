#include <iostream>
#include <algorithm>
#include <chrono>
#include <CoreWindow.h> 
#include <fstream>
using namespace std;
string red = "\033[31m";
string green = "\033[32m";
string zero = "\033[0m";
void PrintX(string pole2[5][6]) {
    cout << "Guess paru\n";
    cout << "  1 2 3 4 5 6\n";
    for (short i = 0; i < 5; i++) {
        cout << char('A' + i) << ' ';
        for (short k = 0; k < 6; k++) {
            cout << pole2[i][k] << zero;
        }
        cout << endl;
    }
}
int main() {
    srand(time(NULL));
    string pole[5][6];
    string pole2[5][6];
    char sym[] = "\1\1\6\6\5\5\4\4\3\3\x11\x11\x12\x12\x15\x15\x14\x14\x13\x13\17\17\16\16\x19\x19\32\32\26\26";
    int count = 0,flips=0,ans=1;
    while (ans == 1) {
        random_shuffle(sym, sym + 30);
        for (short i = 0; i < 30; i++) {
            cout << sym[i] << " ";
        }
        cout << "\nRemember paru: \n";
        cout << "  1 2 3 4 5 6\n";
        for (short i = 0; i < 5; i++) {
            cout << char('A' + i) << ' ';
            for (short k = 0; k < 6; k++) {
                pole[i][k] = sym[i * 6 + k];
                cout << pole[i][k] << " ";
                pole2[i][k] = red + "X ";
            }
            cout << endl;
        }
        auto startPlayer = chrono::steady_clock::now();
        do {
            Sleep(4000);
            system("cls");
            PrintX(pole2);
            cout << "Input leter's number(A=1,B=2,C=3,D=4,E=5) and number first card and second(with space): ";
            int col1, col2, l1, l2;
            string par1, par2, let1, let2;
            cin >> l1 >> col1 >> l2 >> col2;
            l1--;
            l2--;
            col1--;
            col2--;
            flips++;
            if (pole[l1][col1] == pole[l2][col2]) {
                count++;
                cout << "  1 2 3 4 5 6\n";
                for (short i = 0; i < 5; i++) {
                    cout << char('A' + i) << ' ';
                    for (short k = 0; k < 6; k++) {
                        if ((i == l1 && k == col1) || (i == l2 && k == col2)) {
                            pole2[i][k] = green + pole[i][k] + " ";
                            cout << pole2[i][k] << zero;
                        }
                        else cout << pole2[i][k] << zero;
                    }

                    cout << endl;
                }
            }
            else if (pole[l1][col1] != pole[l2][col2]) {
                for (short i = 0; i < 5; i++) {
                    if (i == l1) let1 = 'A' + i;
                    if (i == l2) let2 = 'A' + i;
                }
                cout << let1 << col1 + 1 << ") " << pole[l1][col1] << " " << let2 << col2 + 1 << ") " << pole[l2][col2] << endl;
                PrintX(pole2);
            }
        } while (count < 15);
        auto endPlayer = chrono::steady_clock::now();
        chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
        double timePlayer = elapsedPlayer.count();
        count = 0;
        cout << "Your result:\n" << "Cards flip: " << flips << "\nTime:" << timePlayer << " seconds";
        ofstream results("results.txt");
        results << "Your result:\n" << "Cards flip: " << flips << "\nTime:" << timePlayer << " seconds";
        results.close();
        cout <<endl<< "Do you want play again [1]Yes [2]No: ";
        cin >> ans;
    }
    cout << "Programm complete";
}
