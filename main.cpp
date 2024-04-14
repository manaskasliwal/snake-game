#include<iostream>


/*
library to pass shell/console commands: c standard library
We use the function "system" to send commands to the console.
*/
#include<cstdlib>


/*
library which includes functions to set the cursors position and over write the console.
*/
// #include<windows.h>

// library to capture the key strokes: console input output library
#include<conio.h>

/*
If we dont seed the random function, the food gets displayed in the same places always.
So to seed the random function we include this file.
*/
#include<ctime>


//(including Snakes.h takes care of the fact that windows.h has been included)
#include "Snake.h"
#include "Snake.cpp"

#include "Food.h"
#include "Food.cpp"

#include "Global.h"

/* 
Concept of "MACROS": 
They are one liner codes.
Instead of defining a function we can define a symbol

int sq(int x){
    return x*x;
}

instead=>

#define sq(x) x*x

similary;
#define WIDTH 50
#define HEIGHT 25

*/


using namespace std;

// defining a snake at the center of the screen : initial position
Snake snake({WIDTH/2,HEIGHT/2},1);

// creating a food object
Food food;

int score;

/*
struct COORD{
    int X;
    int Y;
};
if not on windows, define the COORD structure
*/

/*
In the coordiante system out computer uses, the y axis is flipped and the x axis is the same.
*/
// int x=10,y=10;

// const int WIDTH=50, HEIGHT=25;  =>defined as macros

void board(){
    COORD snake_pos=snake.get_pos();
    COORD food_pos=food.get_pos();

    vector<COORD> snake_body=snake.get_body();
    cout<<"SCORE : "<<score<<"\n\n";

    for(int i=0;i<HEIGHT;i++){
        cout<<"\t\t";
        cout<<"#";
        for(int j=0;j<WIDTH-2;j++){
            if(i==0 || i==HEIGHT-1)cout<<"#";
            else if(i==snake_pos.Y and j+1==snake_pos.X) cout<<"0";
            else if(i==food_pos.Y and j+1==food_pos.X) cout<<"X";
            else {
                bool is_body_part=0;
                for(int k=0;k<snake_body.size()-1;k++){
                    if(i==snake_body[k].Y and j+1==snake_body[k].X){
                        cout<<"o";
                        is_body_part=1;
                        break;
                    }
                }
                if(!is_body_part)cout<<" ";
            }
        }
        cout<<"#\n";
    }
}

int main(){
    score=0;
    srand(time(NULL));
    food.gen_food();
    bool gameOver=false;

    while(!gameOver){
        board();

        //detects keyborad hit
        if(kbhit()){
            // gives which key is pressed
            switch(getch()){
                case 'w':{
                    snake.change_dir('u');
                    break;
                }
                case 's':{
                    snake.change_dir('d');
                    break;
                }
                case 'a':{
                    snake.change_dir('l');
                    break;
                }
                case 'd':{
                    snake.change_dir('r');
                    break;
                }
                case 22472:{
                    snake.change_dir('u');
                    break;
                }
                case 22480:{
                    snake.change_dir('d');
                    break;
                }
                case 22475:{
                    snake.change_dir('l');
                    break;
                }
                case 22477:{
                    snake.change_dir('r');
                    break;
                }

                //  22472, 22477, 22480, 22475 for up, right, down and left

            }
        }

        if(snake.collided())gameOver=1;
        if(snake.eaten(food.get_pos())){
            food.gen_food();
            snake.grow();
            score+=10;
        }

        
        snake.move_snake();

        // x++;
        // system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 7});

    }
}
