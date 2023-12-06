#include <iostream>
#include <curses.h>
#include<string>
#include "wincursor.h"
Screen myScreen;
String sp(" ", 10, 10);

struct graphic {
    int dy;
    int dx;
};

struct Tetromino {
    graphic s[8];
};

Tetromino t[7] = {
    1,50, 1,51, 1,52, 1,53, 1,54, 1,55, 1,56, 1,57,
    0,50, 1,50, 0,51, 1,51, 1,52, 1,53, 1,54, 1,55,
    1,50, 1,51, 1,52, 1,53, 1,54, 0,54, 0,55, 1,55,
    0,50, 1,50, 0,51, 1,51, 0,52, 1,52, 0,53, 1,53,
    1,50, 1,51, 1,52, 0,52, 1,53, 0,53, 0,54, 0,55,
    1,50, 1,51, 1,52, 0,52, 0,53, 1,53, 1,54, 1,55,
    0,50, 0,51, 0,52, 1,52, 0,53, 1,53, 1,54, 1,55 };

Tetromino t1[7] = {
    1,50, 1,51, 2,50, 2,51, 3,50, 3,51, 4,50, 4,51,
    0,50, 1,50, 0,51, 1,51, 0,52, 2,50, 2,51, 0,53,
    0,50, 0,51, 1,50, 1,51, 2,50, 2,51, 2,53, 2,52,
    0,50, 1,50, 0,51, 1,51, 0,52, 1,52, 0,53, 1,53,
    0,50, 0,51, 1,50, 1,51, 1,52, 2,52, 1,53, 2,53,
    0,50, 1,50, 2,50, 0,51, 1,51, 2,51, 1,52, 1,53, 
    1,50, 2,50, 1,51, 2,51, 0,52, 1,52, 0,53, 1,53 };

Tetromino t2[7] = {
    1,50, 1,51, 1,52, 1,53, 1,54, 1,55, 1,56, 1,57,
    0,50, 0,51, 0,52, 0,53, 0,54, 0,55, 1,54, 1,55,
    0,50, 0,51, 1,50, 1,51, 0,52, 0,53, 0,54, 0,55,
    0,50, 1,50, 0,51, 1,51, 0,52, 1,52, 0,53, 1,53,
    1,50, 1,51, 1,52, 0,52, 1,53, 0,53, 0,54, 0,55,
    0,50, 0,51, 0,52, 0,53, 0,54, 0,55, 1,52, 1,53, 
    0,50, 0,51, 0,52, 1,52, 0,53, 1,53, 1,54, 1,55 };

Tetromino t3[7] = {
    1,50, 1,51, 2,50, 2,51, 3,50, 3,51, 4,50, 4,51,
    2,50, 2,51, 0,52, 1,52, 2,52, 0,53, 1,53, 2,53, 
    0,50, 0,51, 0,52, 0,53, 1,52, 1,53, 2,52, 2,53, 
    0,50, 1,50, 0,51, 1,51, 0,52, 1,52, 0,53, 1,53,
    0,50, 0,51, 1,50, 1,51, 1,52, 2,52, 1,53, 2,53,
    1,50, 1,51, 0,52, 0,53, 1,52, 1,53, 2,52, 2,53, 
    1,50, 2,50, 1,51, 2,51, 0,52, 1,52, 0,53, 1,53 };

int savedpos[21][26] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9} };

int pos_x[8];
int pos_y[8];
int score;
int high;
int rotate;
int firstblock;
int secondblock;
int randomcolor;// new falling block`s color
int random_x;//new falling block`s x pos
int move_x;//right left moving value
int nonzero;//check row savedpos can be clear or not
bool falling = true;//default the block is falling
bool moving = true;//default the block can moving
bool finished = false;//default the game is not finish
bool removerow = false;//default clear the horizon block is false
void Createblock();
void Checkbottom();
void Checkmoving(int n);
void Checkhorizon();
void Gameover();
void End();
void Drawblock();
void Eraseblock();
void Updatefalling();
void Drawborder();
void PrintScore();
void Printkeydown(char c);
void Control(char c);

int main() {
    char keydown;
    Drawborder();
    Screen myScreen;
    myScreen.setTimeOut(100);   // millisecond
    finished = false;
    score = 0;
    secondblock = (rand() % 7) + 1;
    while (!finished) {
        Createblock();
        PrintScore();
        rotate = 4;
        falling = true;//default the block can fall
        moving = true;//default the block can move
        removerow = false;//default row block can not be removed
        for (high = 0; high < 20; ++high) {
            Drawblock();
            keydown = myScreen.key();
            Printkeydown(keydown);
            Checkbottom();
            Eraseblock();
            Control(keydown);
            myScreen.redraw();
            Checkhorizon();
            Updatefalling();
            Gameover();
            if (finished) break;
            if (!falling) break;
        }
        //printf("%d,%d,%d ", firstblock, secondblock, randomcolor);
    }
    return 0;
}

void Createblock() {
    int temp;
    firstblock = secondblock;
    temp = (rand() % 7) + 1;
    secondblock = temp;
    randomcolor = firstblock;
    //randomcolor = 1;
    random_x = (rand() % 9) * 2;
    move_x = 0;
    sp.setText(" ");
    for (int i = 0; i <= 7; i++) {
        sp.show(t[secondblock - 1].s[i].dy + 10 , t[secondblock - 1].s[i].dx -25, 0);                        
    }
    myScreen.redraw();
    for (int i = 0; i <= 7; i++) {
        sp.show(t[secondblock - 1].s[i].dy + 10, t[secondblock - 1].s[i].dx -25, secondblock);
    }
    myScreen.redraw();
}
void Checkbottom() {//use color n to check it is itselves or other block in savedpos
    for (int i = 0; i < 8; i++) {
        if (savedpos[pos_y[i]][pos_x[i] - 50] != 0) {
            falling = false;
            for (int j = 0; j < 8; j++) {
                savedpos[pos_y[j] - 1][pos_x[j] - 50] = randomcolor;
            }
            break;
        }
        //printf("%d,  ", savedpos[pos_y[i]][pos_x[i] - 50]);
    }
    //printf("\n"); 
}

void Checkmoving(int n) {
    for (int i = 0; i < 8; i++) {
        if (savedpos[pos_y[i]][pos_x[i] - 51] != 0) {
            moving = false;
            break;
        }
        else if (savedpos[pos_y[i]][pos_x[i] - 49] != 0) {
            moving = false;
            break;
        }
        moving = true;
        //printf("%d,  ", savedpos[pos_y[i]][pos_x[i] - 50]);
    }
}

void Checkhorizon() {   
    for (int h = 0; h < 20; h++) {
        nonzero = 0;
        for (int i = 0; i < 26; i++) {
            if (savedpos[h][i] == 0) {
                break;
            }
            else {
                nonzero++;
            }
        }       
        if (nonzero == 26) {
            for (int j = 50; j <= 75; j++) {
                sp.show(h, j, 0);
            }
            myScreen.redraw();
            for (int i = h; i > 0; i--) {
                for (int j = 0; j < 26; j++) {
                    savedpos[i][j] = savedpos[i - 1][j];
                }
            }
            score++;
        }
    }
}

void Gameover() {
    for (int i = 0; i < 26; i++) {
        if (savedpos[1][i] != 0) {
            finished = true;
            End();
            break;
        }
    }
}

void End() {
    myScreen.redraw();
    for (int i = 0; i < 23; i++) {
        sp.setText("                       ---------Game    Over---------");
        sp.show(i, 25, 0); 
        myScreen.redraw();
        sp.setText("                                                     ");
        Sleep(300);
        sp.show(i, 25, 0);
        myScreen.redraw();
    }
    sp.setText("Tetris");
    sp.show(3, 63, 0);
    sp.setText("---Game  Over---");
    sp.show(5, 58, 0);
    sp.setText("Your Score:     " + std::to_string(score));
    sp.show(6, 58, 0);
    sp.setText("Made By TY.Cheng");
    sp.show(20, 58, 0);
    sp.setText("----------------");
    sp.show(21, 58, 0);
    myScreen.redraw();
    Sleep(1000);
}
void Drawblock() {
    if (rotate % 4 == 0) {
        for (int i = 0; i <= 7; i++) {
            sp.show(t[randomcolor - 1].s[i].dy + high, t[randomcolor - 1].s[i].dx + random_x+move_x, randomcolor);
            pos_x[i] = t[randomcolor - 1].s[i].dx + random_x + move_x;
            pos_y[i] = t[randomcolor - 1].s[i].dy + high;
            if (!falling) {
                savedpos[t[randomcolor - 1].s[i].dy + high - 1][t[randomcolor - 1].s[i].dx + random_x + move_x - 50] = randomcolor;
            }
        }
    }
    else if (rotate % 4 == 1) {
        for (int i = 0; i <= 7; i++) {
            sp.show(t1[randomcolor - 1].s[i].dy + high, t1[randomcolor - 1].s[i].dx + random_x + move_x, randomcolor);
            pos_x[i] = t1[randomcolor - 1].s[i].dx + random_x + move_x;
            pos_y[i] = t1[randomcolor - 1].s[i].dy + high;
            if (!falling) {
                savedpos[t1[randomcolor - 1].s[i].dy + high - 1][t1[randomcolor - 1].s[i].dx + random_x+ move_x - 50] = randomcolor;
            }
        }
    }
    else if (rotate % 4 == 2) {
        for (int i = 0; i <= 7; i++) {
            sp.show(t2[randomcolor - 1].s[i].dy + high, t2[randomcolor - 1].s[i].dx + random_x+move_x, randomcolor);
            pos_x[i] = t2[randomcolor - 1].s[i].dx + random_x+move_x;
            pos_y[i] = t2[randomcolor - 1].s[i].dy + high;
            if (!falling) {
                savedpos[t2[randomcolor - 1].s[i].dy + high - 1][t2[randomcolor - 1].s[i].dx + random_x+move_x - 50] = randomcolor;
            }
        }
    }
    else if (rotate % 4 == 3) {
        for (int i = 0; i <= 7; i++) {
            sp.show(t3[randomcolor - 1].s[i].dy + high, t3[randomcolor - 1].s[i].dx + random_x+move_x, randomcolor);
            pos_x[i] = t3[randomcolor - 1].s[i].dx + random_x+move_x;
            pos_y[i] = t3[randomcolor - 1].s[i].dy + high;
            if (!falling) {
                savedpos[t3[randomcolor - 1].s[i].dy + high - 1][t3[randomcolor - 1].s[i].dx + random_x+move_x - 50] = randomcolor;
            }
        }
    }
    myScreen.redraw();
}

void Eraseblock() {
    if (falling) {
        for (int i = 0; i <= 7; i++) {
            sp.show(pos_y[i], pos_x[i], 0);
        }
        myScreen.redraw();
    }
}

void Updatefalling() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 26; j++) {
            sp.show(i, j + 50, 0);
        }
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 26; j++) {
            sp.show(i + 1, j + 50, savedpos[i][j]);
        }
    }
}

void Drawborder() {//50-75
    for (int Long = 0; Long <= 20; Long++) {
        sp.setText("..");
        sp.show(Long, 48, 0);
        sp.show(Long, 76, 0);
    }
    for (int width = 50; width <= 75; width++) {
        sp.setText(".");
        sp.show(21, width, 0);
        sp.show(22, width, 0);
    }
    myScreen.redraw();
    sp.setText(" ");
    for (int i = 3; i > 0; i--) {
        sp.setText(std::to_string(i));
        sp.show(10, 63, 0); 
        myScreen.redraw();
        Sleep(1000);
    }
    sp.setText("START!");
    sp.show(10, 60, 0);
    myScreen.redraw();
    Sleep(1000);
}

void PrintScore() {
    sp.setText("Tetris 1.0");
    sp.show(0, 25, 0); 
    myScreen.redraw();
    sp.setText(" ");
    sp.setText("Line   " + std::to_string(score));
    sp.show(2, 25, 0); 
    myScreen.redraw();
    sp.setText(" ");
    sp.setText("nonzero   " + std::to_string(nonzero));
    sp.show( 4, 25, 0); 
    myScreen.redraw();
    sp.setText(" ");
}
void Printkeydown(char c) {
    switch (c) {
    case'a':
        c = '<';
        break;
    case'd':
        c = '>';
        break;
    default:
        c = 'v';
        break;
    }
    sp.setText("moving  " + std::string(1, c));
    sp.show(3, 25, 0); 
    myScreen.redraw();
    sp.setText(" ");
}

void Control(char c) {
    Checkmoving(randomcolor);
    switch (c) {
    case 'q':
        finished = true;
        break;
    case 'a':
        if (pos_x[0] > 50 && moving == true) {
            move_x -= 2;
            high--;
            break;
        }
        high--;
        break;
    case 'd':
        if (pos_x[7] < 75 && moving == true) {
            move_x += 2;
            high--;
            break;
        }
        high--;
        break;
    case 'w':
        rotate++;
        high--;
        break;
    case ' ':
        int minhigh = 21;
        for (int i = 0; i < 8; i++) {
            for (int j = pos_y[i]; j < 21; j++) {
                if (savedpos[j][pos_x[i] - 50] != 0) {
                    if (j <= minhigh) {
                        minhigh = j;
                    }
                }
            }
        }
        if (rotate % 2 == 0) {
            high = minhigh - 2;
        }
        else {
            high = minhigh - 5;
        }
        
        break;
    }
}
