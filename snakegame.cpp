#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool gameover;
int height = 20, width = 20;
int x, y;
int fruitX, fruitY;
int score;
int tailX[100], tailY[100];
int Ltail{0};

enum direction
{
    Left = 1,
    Right,
    Up,
    Down
};
direction dir;

void draw()
{
    // To stop flickering of screen
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0}); // windows.h

    // To stop flickering of cursor
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info); // windows.h

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
                cout << "# ";

            else if (j == 0 || j == width - 1)
                cout << "# ";

            else if (i == fruitY && j == fruitX)
                cout << "F ";

            else if (i == y && j == x)
                cout << "O ";

            else
            {
                bool print = false;
                for(int k = 0; k < Ltail; k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout << "o ";
                        print = true;
                    }
                }
                if(!print)
                cout << "  ";
            }
                
        }

        cout << endl;
    }

    cout << "Score: " << score << endl;
}

void setup()
{
    gameover = false;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    score = 0;
}

void input()
{
    if (_kbhit()) // input from keyboard
    {
        switch (_getch()) // conio.h lib
        {
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        case 'w':
            dir = Up;
            break;
        case 's':
            dir = Down;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void logic()
{
    int prevX, prevY;
    int prev2X, prev2Y;
    prevX = tailX[0];
    prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < Ltail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    case Up:
        y--;
        break;
    case Down:
        y++;
        break;
    default:
        break;
    }

    // checking collision
    if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
    {
        gameover = true;
    }
    // Checking collision complete!

    //Checking if snake bites itself
    for(int i = 0; i < Ltail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
        gameover = true;
    }
    //Checking bite itself completed!

    //Updating score, new fruit loc, tail length.
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        Ltail++;
    }
    //Updation for score,...,. complete!
}

int main()
{
    setup();
    while (!gameover)
    {
        srand(time(0));
        draw();
        input();
        logic();
        Sleep(100);
    }

    cout << "Game over!" << endl;
    cout << "Your Score: " << score << endl;
}
