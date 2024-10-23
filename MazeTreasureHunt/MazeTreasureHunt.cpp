#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int W = 70;
const int H = 20;
vector<string> map; // Store the map

void LoadMap(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening map file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.size() >= W) {  // Ensure the line width matches the expected width
            map.push_back(line.substr(0, W)); // Store only the first W characters
        }
        else {
            // Fill with spaces if the line is shorter than W
            line.resize(W, ' ');
            map.push_back(line);
        }
    }

    // Fill the rest of the map if there are fewer than H lines
    while (map.size() < H) {
        map.push_back(string(W, ' ')); // Fill with empty spaces
    }

    file.close();
}

void Positions(int pX, int pY, int tX, int tY) {
    system("cls");  // Clear screen after every input
    // Draw the map
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (x == pX && y == pY) {
                cout << "M";  // Player character
            }
            else if (x == tX && y == tY) {
                cout << "$";  // Collectible item
            }
            else {
                cout << map[y][x];  // Map character
            }
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Initialize the random number generator

    LoadMap("Maze.txt");  // Load the map from the file

    // Randomize player position within the map boundaries
    int PX, PY/*, TX,TY*/;
    do {
        PX =  21;
        PY =  3;
        
    } while (map[PY][PX] != ' '); // Ensure the player starts in an empty space

    // Find treasure position on the map
    int TX = 5, TY = 10;
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (map[y][x] == '$') {
                TX = x;
                TY = y;
                break;
            }
        }
        if (TX != -1) break; // Exit if treasure found
    }

    char input;

    do {
        Positions(PX, PY, TX,TY);

        input = _getch();  // Get user input without waiting for Enter key

        switch (input) {
        case 'w': case 'W':
            if (PY > 0 && map[PY - 1][PX] == ' ') PY--;
            break;
        case 's': case 'S':
            if (PY < H - 1 && map[PY + 1][PX] == ' ') PY++;
            break;
        case 'a': case 'A':
            if (PX > 0 && map[PY][PX - 1] == ' ') PX--;
            break;
        case 'd': case 'D':
            if (PX < W - 1 && map[PY][PX + 1] == ' ') PX++;
            break;
        }

        // Check if the player collected the item
        if (PX == TX && PY == TY) {
            system("cls");
            cout << "WINNER WINNER CHICKEN DINNER YOU GOT THE TREASURE!" << endl;
            break;
        }

    } while (input != 'q');

    return 0;
}
