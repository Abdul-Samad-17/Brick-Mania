#ifndef RushHour_CPP_
#define RushHour_CPP_

#include "util.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
using namespace std;

Mix_Music* menuMusic;
Mix_Chunk* smash;
Mix_Chunk* bounce;
Mix_Chunk* tryagain;
Uint32 lastArrowSoundTime = 0;
const Uint32 arrowCooldown = 200; // milliseconds
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void GameDisplay();
void NonPrintableKeys(int, int, int);
void PrintableKeys(unsigned char, int, int);
void MouseClicked(int, int, int, int);
void MouseMoved(int, int);
void MousePressedAndMoved(int, int);
void Timer(int);


class Board{
int board[50][50][3];

public: 
  Board(){
  
      for(int i=0 ; i<50 ; i++){
          for(int j=0 ; j<50 ; j++){
              for(int k=0 ; k<3 ; k++){
                  board[i][j][k]=0;
          }
        }
      }
    }

 void setvalue(int x,int y,int z,int n){
  board[x][y][z]=n;
  }
  
  int getvalue(int x,int y,int z){
  return board[x][y][z];
  }
  
  void display() {
        for (int i = 0; i < 50; i++) {
            if(i<10)
            cout << "Row " << i << ":  ";
            else
            cout << "Row " << i << ": ";
            for (int j = 0; j < 50; j++) {
                //cout << "[";
                for (int k = 0; k < 3; k++) {
                    cout << board[i][j][k];
                }
                cout << " ";
            }
            cout <<endl;
        }
    }

};

class GameObjects{
protected:
int x;
int y;
int size;
};

class UpperBalls : public GameObjects{

public:
UpperBalls(){
x=0;y=0;
size=15;   // so 15 x 15
}

void setx(int x){this->x=x;}
void sety(int y){this->y=y;}
void display(){
DrawSquare(x,y,size,colors[RED]);
}

};

class HoverBoard : public GameObjects{
int length;
int height;
public:
HoverBoard(){length=105,height=15;}
void setx(int x){this->x=x;}
void sety(int y){this->y=y;}
void setl(int l){length=l;}
void seth(int h){height=h;}
void display(){
DrawRectangle(x,y,length,height, colors[BLUE]);
}

};

class BouncingBall : public GameObjects{

public:
BouncingBall(){x=0;y=0;size=7;}
void setx(int x){this->x=x;}
void sety(int y){this->y=y;}
void display(){
DrawCircle(x,y,size,colors[GREEN]);
}

};

class EnergyBoasts{
int x;
int y;
public:

EnergyBoasts(){x=0;y=0;}
void setxy(int x , int y){
this->x=x;
this->y=y;
}
void display(int type){
if(type==5){
DrawRectangle(y*15+5,745-(x*15),15,15, colors[BLUE]);
}
else if(type==6)
DrawRectangle(y*15+5,745-(x*15),15,15, colors[GREEN]);
}

};

// --- Game class (no singleton) ---
class Game {
private:
// Objects
Board board;
UpperBalls **upperballs;
HoverBoard hoverboard;
BouncingBall ball;
EnergyBoasts nos;

// Veriables
bool start;

float TIME;
int count;
int SCORE;
int start_x_upper;
int start_y_upper;
int hoverboard_length;
bool gamestart;
bool moveball;
bool newboard;
bool moveboaster;
//------------------------------------ Hover Board Veriables
bool hmove_left;
bool hmove_right;
int hoverxi;
int hoveryi;
int hx;
int hy;
int hxi;
int hyi;
int hyend;
int hymid;
int hxii;
int hyii;
//------------------------------------- Bouncing Ball Veriables
int numofballs;
int ballxi;
int ballyi;
int ballx;
int bally;
int bxi;
int byi;
int speedx;
int speedy;
bool movediagonal;
bool moveball_up;
bool moveball_down;
int bxii;
int byii;
//------------------------------------ Energy Boasts Veriables
int *nosx;
int *nosy;
int *type;
float noshtime;
float nosstime;
bool cancelnos5;
bool cancelnos6;
bool drawshield;

public:
    Game() {
        // initialize exactly as you did before:
        start=true;
        TIME=0.0;
        SCORE=0;
        newboard=true;
        gamestart=true;
        moveball=false;
        hmove_left=true;
        hmove_right=true;
        start_x_upper=5;
        start_y_upper=735;
        hoverxi=335;
        hoveryi=77;
        hx=hoverxi;
        hy=hoveryi;
        hxii=44;
        hyii=22;
        hxi=44;
        hyi=22;
        hoverboard_length=6;
        hyend=hyi+hoverboard_length;
        hymid=hyi+hoverboard_length/2;
        count=TIME;
        noshtime=0.0;
        nosstime=0.0;
        
        ballxi=387;
        ballyi=98;
        ballx=ballxi;
        bally=ballyi;
        bxi=43;
        byi=25;
        speedx=15;
        speedy=15;
        movediagonal=false;
        moveball_up=false;
        moveball_down=false;
        bxii=bxi;
        byii=byi;
        numofballs=3;
        moveboaster=false;
        cancelnos5=false;
        cancelnos6=false;
        drawshield=false;
        
    upperballs=new UpperBalls*[30];
    for(int i=0 ; i<30 ; i++){
    upperballs[i]=new UpperBalls[50];
    }
    for(int i=0 ; i<30 ; i++){
    for(int j=0 ; j<50 ; j++){
    upperballs[i][j].setx(start_x_upper);
    upperballs[i][j].sety(start_y_upper);
    start_x_upper+=15;
    }
    start_x_upper=5;
    start_y_upper-=15;
    }
    hoverboard.setx(hoverxi);
    hoverboard.sety(hoveryi);
    hoverboard.setl(hoverboard_length*15+15);
    ball.setx(ballxi);
    ball.sety(ballyi);
     cout<<"ballyi: "<<ballyi<<endl;
    
    srand(time(0));
    
    nosx=new int[500];
    nosy=new int[500];
    type=new int[500];
    
    
    }

    ~Game() {
     for(int i=0 ; i<30 ; i++){
    delete []upperballs[i];
    }
    delete []upperballs;
    
    delete []nosx;
    delete []nosy;
    delete []type;
    
    }

    // GlutDisplayFunc
     void display()
{
if(start){
if(newboard){
for(int i=0 ; i<30 ; i++){
for(int j=0 ; j<50 ; j++){
board.setvalue(i,j,0,1);
}
}

for(int i=0 ; i<500 ; i++){
nosx[i]=rand()%(30);
nosy[i]=rand()%(50);
type[i]=rand()%(6-5+1)+5;
board.setvalue(nosx[i],nosy[i],1,type[i]);
}


newboard=false;
}
for(int i=30 ; i<50 ; i++){
for(int j=0 ; j<50 ; j++){
board.setvalue(i,j,0,0);
}
}
for(int i=hxi ; i<hxi+1 ; i++){
for(int j=hyi ; j<=hyend ; j++){
if(j!=hymid)
board.setvalue(i,j,0,3);
else
board.setvalue(i,j,0,2);
}
}
cout<<"bxi: "<<bxi<<"  byi: "<<byi<<endl;
board.setvalue(bxi,byi,0,4);
start=false;
board.display();
}
    
    

    glClearColor(1, 1, 1, 1);    // White background
    glClear(GL_COLOR_BUFFER_BIT);
    

    // Draw UI elements
    DrawString(60, 780, "Score=" + Num2Str(SCORE), colors[BLACK]);
    //DrawString(170, 780, "Time=" + 0, colors[BLACK]);
    DrawString(335, 780, "Time=" + Num2Str(TIME), colors[BLACK]);
    DrawString(585, 780, "Balls=", colors[BLACK]);
    for(int i=0 ; i<numofballs ; i++){
    DrawCircle(650+(15*i+10),788,7,colors[GREEN]);
    }
    //DrawRectangle(550,775 , 148, 25, colors[RED]);
    
    // Draw borders
    DrawLine(757, 6, 757, 750, 100, colors[BLACK]);
    DrawLine(2, 6, 2, 750, 100, colors[BLACK]);
    DrawLine(0, 750, 760, 750, 100, colors[BLACK]);
    DrawLine(0, 3, 760, 3, 15, colors[BLACK]);
    
    if(drawshield)
    DrawRectangle(5,5,745,30, colors[RED]);

    // Draw grid lines
    /*int line_pos_x = 20, line_pos_y1 = 6, line_pos_y2 = 750;
    for (int i = 0; i < 50; i++)
    {
        DrawLine(line_pos_x, line_pos_y1, line_pos_x, line_pos_y2, 1, colors[BROWN]);
        line_pos_x += 15;
    }
    */
    //DrawLine(5, 290, 755, 290, 10, colors[BROWN]);
    

  
        //DrawCircle(55,670,10,colors[GREEN]);
	//DrawCircle(65,680,10,colors[GREEN]);
	//DrawCircle(75,670,10,colors[GREEN]);
	//DrawLine(65, 630, 65, 665, 20, colors[BROWN]);
	//DrawRoundRect(690,635,50,110,colors[RED],70);
	
	
	for(int i=0 ; i<30 ; i++){
        for(int j=0 ; j<50 ; j++){
          if(board.getvalue(i,j,0)==1)
          upperballs[i][j].display();
        }
        }
        hoverboard.display();
        ball.display();
        
        for(int i=0 ; i<500 ; i++){
        if(board.getvalue(nosx[i],nosy[i],2)==7){
          nos.display(type[i]);
      }
    }
    

        
	 glutSwapBuffers();
	}
    // glutTimerFunc
    void update() {
        // --- your update logic from Game::update() ---
        glutPostRedisplay();
        glutTimerFunc(100.0, Timer, 0);  // 60 FPS
        TIME+=0.1;
        
        if(moveball){
        
      if(byi<1 || byi>48){
      speedx=-speedx;
      Mix_PlayChannel(-1, bounce, 0);
      }
      if(bxi<1){
      speedy=-speedy;
      Mix_PlayChannel(-1, bounce, 0);
      }
     // if(ballx<5 || ballx>745)
      //speedx=-speedx;
      
      
      
      
      if( (board.getvalue(bxi-1,byi,0)==0) && ((board.getvalue(bxi+1,byi,0)==2) || (board.getvalue(bxi+1,byi,0)==3))){
      if((board.getvalue(bxi+1,byi,0)==3))
      movediagonal=true;
      else if(board.getvalue(bxi+1,byi,0)==2)
      movediagonal=false;
      if(moveball_up!=moveball_down)speedy=-speedy;
      moveball_up=true;
      moveball_down=false;
      Mix_PlayChannel(-1, bounce, 0);
      }
      if(!movediagonal){
      if(board.getvalue(bxi-1,byi,0)==1 && moveball_up){
      board.setvalue(bxi-1,byi,0,0);
      if(board.getvalue(bxi-1,byi,1)!=0){
        board.setvalue(bxi-1,byi,2,7);
        nos.setxy(bxi-1,byi);
        nos.display(board.getvalue(bxi-1,byi,1));
        board.setvalue(bxi-1,byi,1,0);
        
      }
      moveball_down=true;
      moveball_up=false;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }
      else if(board.getvalue(bxi+1,byi,0)==1 && speedy<0){
      board.setvalue(bxi+1,byi,0,0);
      if(board.getvalue(bxi+1,byi,1)!=0){
        board.setvalue(bxi+1,byi,2,7);
        nos.setxy(bxi+1,byi);
        nos.display(board.getvalue(bxi+1,byi,1));
        board.setvalue(bxi+1,byi,1,0);
        
      }
      moveball_down=false;
      moveball_up=true;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }}
      
      else if(movediagonal){
      if(board.getvalue(bxi-1,byi,0)==1 && moveball_up){
      board.setvalue(bxi-1,byi,0,0);
      if(board.getvalue(bxi-1,byi,1)!=0){
        board.setvalue(bxi-1,byi,2,7);
        nos.setxy(bxi-1,byi);
        nos.display(board.getvalue(bxi-1,byi,1));
        board.setvalue(bxi-1,byi,1,0);
        
      }
      moveball_down=true;
      moveball_up=false;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }
      else if(board.getvalue(bxi-1,byi+1,0)==1 && moveball_up){
      board.setvalue(bxi-1,byi+1,0,0);
      if(board.getvalue(bxi-1,byi+1,1)!=0){
        board.setvalue(bxi-1,byi+1,2,7);
        nos.setxy(bxi-1,byi+1);
        nos.display(board.getvalue(bxi-1,byi+1,1));
        board.setvalue(bxi-1,byi+1,1,0);
        
      }
      moveball_down=true;
      moveball_up=false;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }
      if(board.getvalue(bxi+1,byi,0)==1 && speedy<0){
      board.setvalue(bxi+1,byi-1,0,0);
      if(board.getvalue(bxi+1,byi,1)!=0){
        board.setvalue(bxi+1,byi,2,7);
        nos.setxy(bxi+1,byi);
        nos.display(board.getvalue(bxi+1,byi,1));
        board.setvalue(bxi+1,byi,1,0);
        
      }
      moveball_down=false;
      moveball_up=true;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }
      else if(board.getvalue(bxi+1,byi+1,0)==1 && speedy<0){
      board.setvalue(bxi+1,byi+1,0,0);
      if(board.getvalue(bxi+1,byi+1,1)!=0){
        board.setvalue(bxi+1,byi+1,2,7);
        nos.setxy(bxi+1,byi+1);
        nos.display(board.getvalue(bxi+1,byi+1,1));
        board.setvalue(bxi+1,byi+1,1,0);
        
      }
      moveball_down=false;
      moveball_up=true;
      speedy=-speedy;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }      
      }
        /*
      else if(board.getvalue(bxi,byi+1,0)==1){
      board.setvalue(bxi,byi+1,0,0);
      moveball_down=true;
      moveball_up=false;
      speedx=-speedx;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }
      else if(board.getvalue(bxi,byi-1,0)==1){
      board.setvalue(bxi,byi-1,0,0);
      moveball_down=true;
      moveball_up=false;
      speedx=-speedx;
      SCORE+=1;
      Mix_PlayChannel(-1, smash, 0);
      }*/
      
      board.setvalue(bxi,byi,0,0);

      if(movediagonal){

      if((board.getvalue(bxi+1,byi,0)==3) && ((board.getvalue(bxi+1,byi+1,0)==2) || (board.getvalue(bxi+1,byi+2,0)==2) || (board.getvalue(bxi+1,byi+3,0)==2) ||    (board.getvalue(bxi+1,byi+4,0)==2) || (board.getvalue(bxi+1,byi+5,0)==2)) && speedx>0){
      speedx=-speedx;
      }
      else if((board.getvalue(bxi+1,byi,0)==3) && ((board.getvalue(bxi+1,byi-1,0)==2) || (board.getvalue(bxi+1,byi-2,0)==2) || (board.getvalue(bxi+1,byi-3,0)==2) || (board.getvalue(bxi+1,byi-4,0)==2) || (board.getvalue(bxi+1,byi-5,0)==2)) && speedx<0){
      speedx=-speedx;
      }
      else if(board.getvalue(bxi,byi+1,0)==3 || board.getvalue(bxi,byi-1,0)==3)
      speedx=-speedx;
      ballx+=speedx;
      if(speedx>0)byi++;
      else byi--;
      }
      if((board.getvalue(bxi+1,byi,0)==8 && !movediagonal)||((board.getvalue(bxi+1,byi+1,0)==8 || board.getvalue(bxi+1,byi-1,0)==8) && movediagonal)){
      speedy=-speedy;
      moveball_up=true;
      moveball_down=false;
      Mix_PlayChannel(-1, bounce, 0);
      }
      if((board.getvalue(bxi,byi+1,0)==3 || board.getvalue(bxi,byi,0)==2)&&(!movediagonal && moveball_up)){
      speedy=-speedy;
      moveball_up=false;
      moveball_down=true;
      Mix_PlayChannel(-1, bounce, 0);
      }
      if((board.getvalue(bxi-1,byi+1,0)==3 || board.getvalue(bxi-1,byi-1,0)==3) && movediagonal && moveball_up){
      speedy=-speedy;
      moveball_up=false;
      moveball_down=true;
      Mix_PlayChannel(-1, bounce, 0);
      }
      if((board.getvalue(bxi-1,byi+1,0)==2 || board.getvalue(bxi-1,byi-1,0)==2) && movediagonal && moveball_up){
      speedy=-speedy;
      moveball_up=false;
      moveball_down=true;
      movediagonal=false;
      Mix_PlayChannel(-1, bounce, 0);
      }
      bally+=speedy;
      if(speedy>0)bxi--;
      else bxi++;
      
    
      ball.setx(ballx);
      ball.sety(bally);
      board.setvalue(bxi,byi,0,4);
      
      if(bxi>48){
      hoverboard.setx(hoverxi);
      hoverboard.sety(hoveryi);
      ball.setx(ballxi);
      ball.sety(ballyi);

      moveball=false;
      bxi=bxii;
      byi=byii;
      hyi=hyii;
      hxi=hxii;
      ballx=ballxi;
      bally=ballyi;
      hx=hoverxi;
      hy=hoveryi;
      hoverboard_length=6;
      hyend=hyi+hoverboard_length;
      hymid=hyi+hoverboard_length/2;
      start=true;
      numofballs--;
      noshtime=0;
      for(int i=0 ; i<500 ; i++){
      if(board.getvalue(nosx[i],nosy[i],2)==7)
      board.setvalue(nosx[i],nosy[i],2,0);
      }
      
      
      Mix_PlayChannel(-1, tryagain, 0);
      if(numofballs==0)
      exit(1);
      }
      count+=1;
      if(count%2==0){
      for(int i=0 ; i<500 ; i++){
        if(board.getvalue(nosx[i],nosy[i],2)==7){
        if((board.getvalue(nosx[i]+1,nosy[i],0)==3 || board.getvalue(nosx[i]+1,nosy[i],0)==2)&&(type[i]==5))
        {
          if(cancelnos5){
          noshtime=10;
          board.setvalue(nosx[i],nosy[i],2,0);
          }
        
          else if(!cancelnos5){
          cancelnos5=true;
          noshtime=10;
          board.setvalue(nosx[i],nosy[i],2,0);
          hoverboard_length=10;
          hymid=hyi+hoverboard_length/2;
          hyend=hyi+hoverboard_length;
          hoverboard.setl(hoverboard_length*15+15);
          if(hyi>1){
            if(hyi>40){
              if(hyi==41){
                hyi-=3;
                hymid=hyi+hoverboard_length/2;
                hyend=hyi+hoverboard_length;
                for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
                   hx-=45;
                   hoverboard.setx(hx);
                }
                else if(hyi==42){
                  hyi-=4;
                  hymid=hyi+hoverboard_length/2;
                  hyend=hyi+hoverboard_length;
                for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
                   hx-=60;
                   hoverboard.setx(hx);
                }
          
          }
          else{
                hyi-=2;
                hymid=hyi+hoverboard_length/2;
                hyend=hyi+hoverboard_length;
                for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
                   hx-=30;
                   hoverboard.setx(hx);
          }
          }
          else{
            if(hyi==1){
              hyi-=1;
              hymid=hyi+hoverboard_length/2;
              hyend=hyi+hoverboard_length;
              for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
                   hx-=15;
                   hoverboard.setx(hx);
            }
            else if(hyi==0){
              hymid=hyi+hoverboard_length/2;
              hyend=hyi+hoverboard_length;
              for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
                   hoverboard.setx(hx);
            }
            
          }
          
          }
        }
        else if((board.getvalue(nosx[i]+1,nosy[i],0)==3 || board.getvalue(nosx[i]+1,nosy[i],0)==2)&&(type[i]==6)){
        board.setvalue(nosx[i],nosy[i],2,0);
        for(int j=0 ; j<50 ; j++){
        board.setvalue(48,j,0,8);
        }
        nosstime=10;
        cancelnos6=true;
        drawshield=true;
        }
        else{
          board.setvalue(nosx[i],nosy[i],2,0);
          nosx[i]++;
          board.setvalue(nosx[i],nosy[i],2,7);
          nos.setxy(nosx[i],nosy[i]);
          
          
          if(nosx[i]>48)
          board.setvalue(nosx[i],nosy[i],2,0);
          }
      }
    }
    }
     noshtime-=0.1;
     nosstime-=0.1;
    }
     
    
    if(noshtime<=0 && cancelnos5){
              for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                      board.setvalue(i,j,0,0);
                    }
                  }
                  hyi+=2;
          hoverboard_length=6;
          hymid=hyi+hoverboard_length/2;
          hyend=hyi+hoverboard_length;
          for(int i=hxi ; i<hxi+1 ; i++){
                  for(int j=hyi ; j<=hyend ; j++){
                    if(j!=hymid)
                      board.setvalue(i,j,0,3);
                    else
                      board.setvalue(i,j,0,2);
                    }
                  }
          hoverboard.setl(hoverboard_length*15+15);
          hx+=30;
          hoverboard.setx(hx);
          cancelnos5=false;
    }
    if(nosstime<=0 && cancelnos6){
    for(int j=0 ; j<50 ; j++){
    board.setvalue(48,j,0,0);
    }
    drawshield=false;
    cancelnos6=false;
    
    }
    
}
     

    // glutSpecialFunc
    void onNonPrintable(int key, int x, int y) {
       /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	 if(hyi<1){
	 hmove_left=false;
	 }
	 else if(hyi>48-hoverboard_length){
	 hmove_right=false;
	 }
	 
	 
	 if (key== GLUT_KEY_LEFT && hmove_left && board.getvalue(hxi,hyi-1,0)==0/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {// what to do when left key is pressed...
              hmove_right=true;
              board.setvalue(hxi,hyend,0,0);
              hyi--;
              board.setvalue(hxi,hyi,0,3);
              board.setvalue(hxi,hymid,0,3);
              hymid--;
              board.setvalue(hxi,hymid,0,2);
              hyend=hyi+hoverboard_length;
              hymid=hyi+hoverboard_length/2;
              hx-=15;
              hoverboard.setx(hx);
              if(!moveball){
              if(speedx>0)
              ballx-=speedx;
              else{
              speedx=-speedx;
              ballx-=speedx;
              }
              board.setvalue(bxi,byi,0,0);
              byi--;
              ball.setx(ballx);
              board.setvalue(bxi,byi,0,4);
              }
              board.display();
              cout<<"hyend"<<hyend<<endl;
	} else if (key== GLUT_KEY_RIGHT && hmove_right  && board.getvalue(hxi,hyend+1,0)==0/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
	      hmove_left=true;
	      board.setvalue(hxi,hyi,0,0);
	      hyi++;
	      hyend=hyi+hoverboard_length;
              board.setvalue(hxi,hyend,0,3);
              board.setvalue(hxi,hymid,0,3);
              hymid++;
              board.setvalue(hxi,hymid,0,2);
              hx+=15;
              hymid=hyi+hoverboard_length/2;
              hoverboard.setx(hx);
              if(!moveball){
              if(speedx>0)
              ballx+=speedx;
              else{
              speedx=-speedx;
              ballx+=speedx;
              }
              board.setvalue(bxi,byi,0,0);
              byi++;
              ball.setx(ballx);
              board.setvalue(bxi,byi,0,4);
              }
              board.display();
              cout<<"hyend"<<hyend<<endl;
	} else if (key== GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
	      board.display();
	}else if (key== GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
	     board.display();
	}

        glutPostRedisplay();
    }

    // glutKeyboardFunc
    void onPrintable(unsigned char key, int x, int y) {
        if (key == 27) exit(1);
        
        if(key==13 && gamestart){
        moveball=true;
        }
        
        if(key=='p'){
        if(moveball)
        moveball=false;
        else moveball=true;
        }
        
        glutPostRedisplay();
    }

    // glutMouseFunc
        void onMouseClick(int buttona, int state, int x, int y) {
    
    
    
        glutPostRedisplay();
    }

    // glutPassiveMotionFunc
    void onMouseMove(int x, int y) {
        // ...
        //glutPostRedisplay();
    }

    // glutMotionFunc
    void onMouseDrag(int x, int y) {
        // ...
        glutPostRedisplay();
    }
};

// --- Global game object ---
static Game game;

// --- Callback wrappers (must match original main) ---
void GameDisplay()                  { game.display(); }
void NonPrintableKeys(int k,int x,int y) { game.onNonPrintable(k,x,y); }
void PrintableKeys(unsigned char k,int x,int y) { game.onPrintable(k,x,y); }
void Timer(int v)                   { game.update(); }
void MouseClicked(int b,int s,int x,int y)   { game.onMouseClick(b,s,x,y); }
void MouseMoved(int x,int y)        { game.onMouseMove(x,y); }
void MousePressedAndMoved(int x,int y) { game.onMouseDrag(x,y); }


// --- Original main (unchanged) ---

int main(int argc, char* argv[]) {
    int width = 760, height = 820;
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("Abdul Samad 24I_0095");
    SetCanvasSize(width, height);
    
    glutDisplayFunc(GameDisplay);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutTimerFunc(1000.0, Timer, 0);
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);
    glutMotionFunc(MousePressedAndMoved);
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    cerr << "SDL_Init failed: " << SDL_GetError() << endl;
    exit(1);
}
if ((Mix_Init(MIX_INIT_MP3) & MIX_INIT_MP3) == 0) {
    cerr << "Mix_Init(MP3) failed: " << Mix_GetError() << endl;
    exit(1);
}
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    cerr << "Audio init failed: " << Mix_GetError() << endl;
    exit(1);  // or return 1
}
   
    menuMusic  = Mix_LoadMUS("menu.mp3");
    smash     = Mix_LoadWAV("smash.mp3");
    bounce   = Mix_LoadWAV("bounce.mp3");
    tryagain   = Mix_LoadWAV("tryagain.mp3");
   Mix_VolumeMusic(MIX_MAX_VOLUME/2);
    //Mix_PlayMusic(menuMusic, -1);
    
    glutMainLoop();
    return 1;
}




#endif /* RushHour_CPP_ */

