#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y;
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

enum eLanguage { ENGLISH, VIETNAMESE };
eLanguage currentLanguage = ENGLISH;

const char* menuTitle_EN = "SNAKE GAME";
const char* startGame_EN = "1. Start Game";
const char* instructions_EN = "2. Instructions";
const char* exit_EN = "3. Exit";
const char* enterChoice_EN = "Enter your choice: ";
const char* instructionsTitle_EN = "INSTRUCTIONS";
const char* moveUp_EN = "Use 'W' to move up";
const char* moveDown_EN = "Use 'S' to move down";
const char* moveLeft_EN = "Use 'A' to move left";
const char* moveRight_EN = "Use 'D' to move right";
const char* exitGame_EN = "Press 'X' to exit the game";
const char* backToMenu_EN = "Press any key to go back to menu...";
const char* invalidChoice_EN = "Invalid choice! Please try again.";
const char* scoreText_EN = "Score: ";

const char* menuTitle_VI = "TRO CHOI RAN";
const char* startGame_VI = "1. Bat dau tro choi";
const char* instructions_VI = "2. Huong dan";
const char* exit_VI = "3. Thoat";
const char* enterChoice_VI = "Nhap lua chon cua ban: ";
const char* instructionsTitle_VI = "HUONG DAN";
const char* moveUp_VI = "Su dung 'W' de di chuyen len";
const char* moveDown_VI = "Su dung 'S' de di chuyen xuong";
const char* moveLeft_VI = "Su dung 'A' de di chuyen trai";
const char* moveRight_VI = "Su dung 'D' de di chuyen phai";
const char* exitGame_VI = "Nhan 'X' de thoat tro choi";
const char* backToMenu_VI = "Nhan phim bat ky de quay lai menu...";
const char* invalidChoice_VI = "Lua chon khong hop le! Vui long thu lai.";
const char* scoreText_VI = "Diem so: ";

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = std::rand() % width;
    fruitY = std::rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    if (currentLanguage == ENGLISH)
        std::cout << scoreText_EN << score << std::endl;
    else
        std::cout << scoreText_VI << score << std::endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void ShowMenu() {
    if (currentLanguage == ENGLISH) {
        cout << "====================" << endl;
        cout << menuTitle_EN << endl;
        cout << "====================" << endl;
        cout << startGame_EN << endl;
        cout << instructions_EN << endl;
        cout << exit_EN << endl;
        cout << enterChoice_EN;
    }
    else {
        cout << "====================" << endl;
        cout << menuTitle_VI << endl;
        cout << "====================" << endl;
        cout << startGame_VI << endl;
        cout << instructions_VI << endl;
        cout << exit_VI << endl;
        cout << enterChoice_VI;
    }
}

void Instructions() {
    if (currentLanguage == ENGLISH) {
        cout << "====================" << endl;
        cout << instructionsTitle_EN << endl;
        cout << "====================" << endl;
        cout << moveUp_EN << endl;
        cout << moveDown_EN << endl;
        cout << moveLeft_EN << endl;
        cout << moveRight_EN << endl;
        cout << exitGame_EN << endl;
        cout << backToMenu_EN;
    }
    else {
        cout << "====================" << endl;
        cout << instructionsTitle_VI << endl;
        cout << "====================" << endl;
        cout << moveUp_VI << endl;
        cout << moveDown_VI << endl;
        cout << moveLeft_VI << endl;
        cout << moveRight_VI << endl;
        cout << exitGame_VI << endl;
        cout << backToMenu_VI;
    }
    _getch();
}

int main() {
    int choice;
    cout << "Select Language / Chon Ngon Ngu:" << endl;
    cout << "1. English" << endl;
    cout << "2. Tieng Viet" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
        currentLanguage = ENGLISH;
        break;
    case 2:
        currentLanguage = VIETNAMESE;
        break;
    default:
        cout << "Invalid choice! Defaulting to English." << endl;
        currentLanguage = ENGLISH;
        break;
    }

    while (true) {
        ShowMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            Setup();
            while (!gameOver) {
                Draw();
                Input();
                Logic();
                Sleep(100);
            }
            break;
        case 2:
            Instructions();
            break;
        case 3:
            return 0;
        default:
            if (currentLanguage == ENGLISH)
                cout << invalidChoice_EN << endl;
            else
                cout << invalidChoice_VI << endl;
            break;
        }
    }
    return 0;
}
