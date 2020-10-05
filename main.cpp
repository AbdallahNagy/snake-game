#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

void shifting(int arr[], int siz)
{
    for(int i=siz-2; i>=0; i--)
        arr[i+1] = arr[i];
}

//direction
enum direction{STOP=0,TOP, DOWN, LEFT, RIGHT};
direction dir;
//map
int width, height, fruitX, fruitY;
//snake
int x, y, snakeTail;
int tail_x[50], tail_y[50];
//player
int score;
bool gameOver;

void generate_fruit()
{
    srand(time(0));
    fruitX = rand() % (width-2)+1;
    fruitY = rand() % (height-2)+1;
}

void setup()
{
    width = 40;
    height = 20;
    generate_fruit();

    x = width /2;
    y = height /2;
    gameOver = false;
    snakeTail = 0;
    score = 0;
    dir = STOP;
}

void draw()
{
    system("cls");
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(i==0 || i==height-1 || j==0 || j==width-1) cout << "*";
            else if(x==j && y==i) cout << "O";
            else if(fruitX==j && fruitY==i) cout<< "$";
            else{
                bool printed = false;
                for(int z=0; z<snakeTail; z++)
                {
                    if(tail_x[z]==j && tail_y[z]==i){
                    cout << "o";
                    printed = true;
                    break;
                    }
                }
                if(!printed) cout << " ";
            }
        }
        cout <<endl;
    }
    cout << "SCORE: " <<score;
}

void input()
{
    if(_kbhit())
    {
        switch(_getch())
        {
            case 'a': dir = LEFT;  break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = TOP;   break;
            case 's': dir = DOWN;  break;
            case 'q': gameOver = 1;
            default : break;
        }
    }
}

void mov()
{
    shifting(tail_x,50);
    shifting(tail_y,50);
    tail_x[0] = x;
    tail_y[0] = y;

    switch(dir)
        {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case TOP:   y--; break;
            case DOWN:  y++; break;
        }

    if(x==fruitX && y==fruitY){
        generate_fruit();
        score += 5;
        snakeTail += 1;
    }

    //if(x==width-1 || x==0 || y==height-1 || y==0) gameOver = true;
    if( x >=width) x = 1;else if(x <= 0) x = width - 1;
	if( y >=height) y = 1;else if(y <= 0) y = height - 1;

    for(int i = 0; i < snakeTail; i++){
		if(tail_x[i] == x && tail_y[i] == y)
			gameOver = true;
    }
}

int main()
{
    setup();
    while(!gameOver){
        draw();
        input();
        mov();
        Sleep(14);
    }

    system("pause");
    return 0;
}
