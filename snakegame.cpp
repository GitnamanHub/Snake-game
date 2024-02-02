#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;

bool gameover;
int height=20,width=20;
int x,y;
int fruitX,fruitY;
int score;

enum direction{Left=1, Right, Up, Down};
direction dir;

void draw()
{
    system("cls");
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==0 || i == height-1)
                cout<<"# ";

            else if(j==0 || j==width-1)
                cout<<"# ";

            else if(i==fruitY && j==fruitX)
                cout<<"F ";

            else if(i==y && j==x)
                cout<<"O ";

            else
                cout<<"  ";

        }

        cout<<endl;
    }

    cout<<"Score: "<<score<<endl;
}

void setup()
{
    gameover = false;
    x=width/2;
    y=height/2;
    fruitX=rand()%(width-2) +1;
    fruitY=rand()%(height-2) +1;
    score=0;
}

void input()
{
    if(_kbhit())
    {
        switch (_getch())
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
    switch(dir)
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

    //checking collision
    if(x<=0 || x>=width-1 || y<=0 || y>=height-1)
    {
        gameover = true;
    }

    if(x==fruitX && y==fruitY)
    {
        score+=10;
        fruitX=rand()%(width-2)+1;
        fruitY=rand()%(height-2)+1;
    }


}


int main()
{
    setup();
    while(!gameover)
    {
        srand(time(0));
        draw();
        input();
        logic();
        Sleep(100);
    }

    cout<<"Game over!"<<endl;
    cout<<"Your Score: "<<score<<endl;
}