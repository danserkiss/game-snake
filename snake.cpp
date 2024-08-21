#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

bool snakedeath = false;
bool* death = &snakedeath;
const int WEIGHT = 12;
const int HEIGHT = 12;

void moveside(char& lastmove, char& move) {
    if (lastmove == 'a' && move == 'd')
        move = 'a';
    else if (lastmove == 's' && move == 'w')
        move = 's';
    else if (lastmove == 'w' && move == 's')
        move = 'w';
    else if (lastmove == 'd' && move == 'a')
        move = 'd';
}

void makemap(char mapp[HEIGHT][WEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WEIGHT; k++) {
            if (i == 0 || i == HEIGHT - 1 || k == 0 || k == WEIGHT - 1)
                mapp[i][k] = '#';
            else
                mapp[i][k] = ' ';
        }
    }
}

void out(const char mapp[HEIGHT][WEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WEIGHT; k++) {
            std::cout << mapp[i][k] << " ";
            if (k == WEIGHT - 1)
                std::cout << std::endl;
        }
    }
}

void eat(char mapp[HEIGHT][WEIGHT], int& eatx, int& eaty) {
    do {
        eatx = 1 + rand() % (WEIGHT - 2);
        eaty = 1 + rand() % (HEIGHT - 2);
    } while (mapp[eatx][eaty] == '0');

    mapp[eatx][eaty] = '*';
}

bool check(const char mapp[HEIGHT][WEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WEIGHT; k++) {
            if (mapp[i][k] == '*')
                return true;
        }
    }
    return false;
}

void snake(char mapp[HEIGHT][WEIGHT], const char snake[], int x, int y, int a, int eatx, int eaty, char lastmove, int cycle, const vector<int>& snakepathx, const vector<int>& snakepathy, bool& snakedeath, bool* death) {
    *death = false;
    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WEIGHT; k++) {
            if (mapp[i][k] != '#' && mapp[i][k] != '*')
                mapp[i][k] = ' ';
        }
    }
    mapp[x][y] = '0';
    for (int i = 0; i < a && cycle - i >= 0; i++) {
        mapp[snakepathx[cycle - i]][snakepathy[cycle - i]] = '0';
        if (i > 1 && mapp[x][y] == mapp[snakepathx[cycle - i - 1]][snakepathy[cycle - i - 1]]) {
            *death = true;
            break;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int k = 0; k < WEIGHT; k++) {
            if (i == 0 || i == HEIGHT - 1 || k == 0 || k == WEIGHT - 1)
                if (i == x && k == y)
                    *death = true;
        }
    }
}

int main() {
    int game = 1;
    vector<int> snakepathx;
    vector<int> snakepathy;
    char lastmove = 'a';
    int cycle = 0;
    int a = 1;
    int eatx, eaty;
    char* SNAKE = new char[WEIGHT * HEIGHT];
    SNAKE[a] = '0';
    char map[HEIGHT][WEIGHT];
    int y = (HEIGHT - 1) / 2;
    int x = (WEIGHT - 1) / 2;
    makemap(map);
    eat(map, eatx, eaty);
    while (game) {
        system("cls");
        snakepathx.push_back(x);
        snakepathy.push_back(y);
        if (!check(map)) {
            a++;
            eat(map, eatx, eaty);
        }
        snake(map, SNAKE, x, y, a, eatx, eaty, lastmove, cycle, snakepathx, snakepathy, snakedeath, death);
        out(map);
        if (*death) {
            std::cout << "gameover" << std::endl;
            std::cout << "your score: " << a;
            delete[] SNAKE;
            cout << endl;
            system("pause");
            return -1;
        }
        std::cout << "your score: " << a;
        char move;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (_kbhit())
            move = _getch();
        else
            move = lastmove;

        moveside(lastmove, move);

        switch (move) {
        case 'a':
            y -= 1;
            break;
        case 'w':
            x -= 1;
            break;
        case 's':
            x += 1;
            break;
        case 'd':
            y += 1;
            break;
        }
        lastmove = move;

        cycle++;
    }
    delete[] SNAKE;
    return 0;
}
