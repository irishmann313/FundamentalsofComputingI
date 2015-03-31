// Brian Mann
// Final project: Fall 2014

#include <stdio.h>
#include <math.h>
#include "gfx3.h"
#include <string.h>

void scoreboard(int,int);

int main()
{
        int width=1000, height=400;
        double  x=width/2, y=height/2;
        char c=0;
        double dx=1,dy=0,dx2=1.5;
        int r=5,player1score=0,player2score=0,i;
        int paddle1x=0, paddle1y1=height/2-20, paddle1y2=height/2+20,paddle2x=width,paddle2y1=height/2-20,paddle2y2=height/2+20;
        char score[7];

        strcpy(score,"Score:");

        gfx_open(width,height, "Final.c");

        // give the user the option to play on easy and hard
        while(c==0){
                gfx_text(width/4,height/2,"Press 'e' for easy, 'h' for hard. 'w' and 's' control player 1 and 'o' and 'l' control player 2.");
                c=gfx_wait();
        }

        // enter switch statement based on user difficulty choice
        switch(c){
                case 'e':
                        // begin the while loop that starts difficulty easy where the ball speeds up at a regular rate and has larger paddles
                        while (c != 'q'){
                                gfx_clear();
                                gfx_color(255,255,255);
                                gfx_text(width/2 - 15, 10, score);
                                scoreboard(player1score,player2score);
                                // add the middle line
                                for(i=0;i<25;i++){
                                        if(i%2==0){
                                                gfx_line(width/2,25*i+5,width/2,25*i+30);
                                        }
                                }
                                gfx_circle(x,y,r);
                                gfx_color(255,0,0);
                                // loop to give the paddles a thickness
                                for(i=0;i<10;i++){
                                        gfx_line(paddle1x+i,paddle1y1,paddle1x+i,paddle1y2);
                                }
                                gfx_color(0,0,255);
                                for(i=0;i<10;i++){
                                        gfx_line(paddle2x-i,paddle2y1,paddle2x-i,paddle2y2);
                                }
                                gfx_flush;
                                x+=dx;
                                y+=dy;
                                usleep(7000);

                                // cause the ball to bounce on the floor and ceiling
                                if (y<r||y>height-r){
                                        dy*=-1;
                                }
                                // increment players' score
                                if (x<0){
                                        player2score++;
                                        x=width/2;
                                        y=height/2;
                                        dx=-1;
                                        dy=0;
                                }else if(x>width){
                                        player1score++;
                                        x=width/2;
                                        y=height/2;
                                        dx=1;
                                        dy=0;
                                        }
                                // determine if the ball hit the paddle or not, speeding up the
                                // ball each time the paddle is hit
                                // y-component changes based on where it hits the paddle
                                if (x-10<r&&(y>=paddle1y1&&y<=paddle1y1+13)){
                                        dx*=-1.15;
                                        dy=-1;
                                }
                                if (x-10<r&&(y>paddle1y1+13&&y<=paddle1y1+26)){
                                        dx*=-1.15;
                                }
                                if (x-10<r&&(y>paddle1y1+26&&y<=paddle1y2)){
                                        dx*=-1.15;
                                        dy=1;
                                }
                                if (x+10>width-r&&(y>=paddle2y1&&y<=paddle2y1+13)){
                                        dx*=-1.15;
                                        dy=-1;
                                }
                                if (x+10>width-r&&(y>paddle2y1+13&&y<=paddle2y1+26)){
                                        dx*=-1.15;
                                }
                                if (x+10>width-r&&(y>paddle2y1+26&&y<=paddle2y2)){
                                        dx*=-1.15;
                                        dy=1;
                                }
                                // end the game if a player reaches 11, with a rule of win-by-two
                                if ((player1score>=11||player2score>=11)&&(abs(player1score-player2score)>=2)){
                                        gfx_clear();
                                        while(c!=' '){
                                                if(player1score>=11&&player1score>player2score){
                                                        gfx_color(255,0,0);
                                                        gfx_text(width/2-100,height/2,"Player 1 wins! (press 'space' to continue)");
                                                }else if(player2score>=11&&player2score>player1score){
                                                        gfx_color(0,0,255);
                                                        gfx_text(width/2-100,height/2,"Player 2 wins! (press 'space' to continue)");
                                                }
                                                c=gfx_wait();
                                        }
                                        gfx_clear();
                                        // give the user a chance to play again
                                        while(c==' '){
                                        gfx_text(width/2-100,height/2,"Press 'r' to play again or 'q' to quit.");
                                                c=gfx_wait();
                                        }
                                }
                                // reset the score
                                if(c=='r'){
                                        player1score=0;
                                        player2score=0;
                                        c=0;
                                }
                                // obtain user input for paddle movement
                                if (gfx_event_waiting()){
                                        c = gfx_wait();
                                        switch (c){
                                                case 'w':
                                                        paddle1y1=paddle1y1-10;
                                                        paddle1y2=paddle1y2-10;
                                                        break;
                                                case 'o':
                                                        paddle2y1=paddle2y1-10;
                                                        paddle2y2=paddle2y2-10;
                                                        break;
                                                case 's':
                                                        paddle1y1=paddle1y1+10;
                                                        paddle1y2=paddle1y2+10;
                                                        break;
                                                case 'l':
                                                        paddle2y1=paddle2y1+10;
                                                        paddle2y2=paddle2y2+10;
                                                        break;
                                        }
                                }
                        }
                break;
                case 'h':
                        // begin the while loop for difficulty hard, where it gets quicker at faster rate and has smaller paddles
                        paddle1y1=height/2-15, paddle1y2=height/2+15,paddle2y1=height/2-15,paddle2y2=height/2+15;
                        while (c != 'q'){
                                gfx_clear();
                                gfx_color(255,255,255);
                                gfx_text(width/2 - 15,10,score);
                                scoreboard(player1score,player2score);
                                // place the center line
                                for(i=0;i<25;i++){
                                        if(i%2==0){
                                                gfx_line(width/2,25*i+5,width/2,25*i+30);
                                        }
                                }
                                gfx_circle(x,y,r);
                                gfx_color(255,0,0);
                                // loop to give the paddles a thickness
                                for(i=0;i<10;i++){
                                        gfx_line(paddle1x+i,paddle1y1,paddle1x+i,paddle1y2);
                                }
                                gfx_color(0,0,255);
                                for(i=0;i<10;i++){
                                        gfx_line(paddle2x-i,paddle2y1,paddle2x-i,paddle2y2);
                                }
                                gfx_flush;
                                x+=dx2;
                                y+=dy;
                                usleep(7000);

                                // cause the ball to bounce on the floor and ceiling
                                if (y<r||y>height-r){
                                        dy*=-1;
                                }
                                // increment players' score
                                if (x<0){
                                        player2score++;
                                        x=width/2;
                                        y=height/2;
                                        dx2=-1.5;
                                        dy=0;
                                }else if(x>width){
                                        player1score++;
                                        x=width/2;
                                        y=height/2;
                                        dx2=1.5;
                                        dy=0;
                                }
                                // determine if the ball hit the paddle or not, speeding up the
                                // ball each time the paddle is hit
                                if (x-10<=r&&(y>=paddle1y1&&y<=paddle1y1+10)){
                                        dx2*=-1.15;
                                        dy=-1;
                                }
                                if (x-10<=r&&(y>paddle1y1+10&&y<=paddle1y1+20)){
                                        dx2*=-1.15;
                                }
                                if (x-10<=r&&(y>paddle1y1+20&&y<=paddle1y2)){
                                        dx2*=-1.15;
                                        dy=1;
                                }
                                if (x+10>=width-r&&(y>=paddle2y1&&y<=paddle2y1+10)){
                                        dx2*=-1.15;
                                        dy=-1;
                                }
                                if (x+10>=width-r&&(y>paddle2y1+10&&y<=paddle2y1+20)){
                                        dx2*=-1.15;
                                }
                                if (x+10>=width-r&&(y>paddle2y1+20&&y<=paddle2y2)){
                                        dx2*=-1.15;
                                        dy=1;
                                }
                                // end the game if a player reaches 11, with a rule of win-by-two
                                if ((player1score>=11||player2score>=11)&&(abs(player1score-player2score)>=2)){
                                        gfx_clear();
                                        while(c!=' '){
                                                if(player1score>=11&&player1score>player2score){
                                                        gfx_color(255,0,0);
                                                        gfx_text(width/2-100,height/2,"Player 1 wins! (press 'space' to continue)");
                                                }else if(player2score>=11&&player2score>player1score){
                                                        gfx_color(0,0,255);
                                                        gfx_text(width/2-100,height/2,"Player 2 wins! (press 'space' to continue)");
                                                }
                                                c=gfx_wait();
                                        }
                                        gfx_clear();
                                        // give the player the chance to play again or quit
                                        while(c==' '){
                                        gfx_text(width/2-100,height/2,"Press 'r' to play again or 'q' to quit.");
                                                c=gfx_wait();
                                        }
                                }
                                // reset the scores
                                if(c=='r'){
                                        player1score=0;
                                        player2score=0;
                                        c=0;
                                }
                                if (gfx_event_waiting()){
                                        c = gfx_wait();
                                        switch (c){
                                                case 'w':
                                                        paddle1y1=paddle1y1-10;
                                                        paddle1y2=paddle1y2-10;
                                                        break;
                                                case 'o':
                                                        paddle2y1=paddle2y1-10;
                                                        paddle2y2=paddle2y2-10;
                                                        break;
                                                case 's':
                                                        paddle1y1=paddle1y1+10;
                                                        paddle1y2=paddle1y2+10;
                                                        break;
                                                case 'l':
                                                        paddle2y1=paddle2y1+10;
                                                        paddle2y2=paddle2y2+10;
                                                        break;
                                        }
                                }
                        }
                break;
        }
}

void scoreboard(int player1score, int player2score)
{
        // could not think of a better way to display the score since gfx_text() requires the third input to be a string
        // probably could have been done using arrays, etc.
        switch(player1score){
                case 0:
                        gfx_text(250,20,"0");
                        break;
                case 1:
                        gfx_text(250,20,"1");
                        break;
                case 2:
                        gfx_text(250,20,"2");
                        break;
                case 3:
                        gfx_text(250,20,"3");
                        break;
                case 4:
                        gfx_text(250,20,"4");
                        break;
                case 5:
                        gfx_text(250,20,"5");
                        break;
                case 6:
                        gfx_text(250,20,"6");
                        break;
                case 7:
                        gfx_text(250,20,"7");
                        break;
                case 8:
                        gfx_text(250,20,"8");
                        break;
                case 9:
                        gfx_text(250,20,"9");
                        break;
                case 10:
                        gfx_text(250,20,"10");
                        break;
                case 11:
                        gfx_text(250,20,"11");
                        break;
                default:
                        if(player1score>player2score){
                                gfx_text(250,20,"Advantage");
                        }else if(player1score==player2score){
                                gfx_text(250,20,"Deuce");
                        }
                        break;
        }
        switch(player2score){
                case 0:
                        gfx_text(750,20,"0");
                        break;
                case 1:
                        gfx_text(750,20,"1");
                        break;
                case 2:
                        gfx_text(750,20,"2");
                        break;
                case 3:
                        gfx_text(750,20,"3");
                        break;
                case 4:
                        gfx_text(750,20,"4");
                        break;
                case 5:
                        gfx_text(750,20,"5");
                        break;
                case 6:
                        gfx_text(750,20,"6");
                        break;
                case 7:
                        gfx_text(750,20,"7");
                        break;
                case 8:
                        gfx_text(750,20,"8");
                        break;
                case 9:
                        gfx_text(750,20,"9");
                        break;
                case 10:
                        gfx_text(750,20,"10");
                        break;
                case 11:
                        gfx_text(750,20,"11");
                        break;
                default:
                        if(player2score>player1score){
                                gfx_text(750,20,"Advantage");
                        }else if(player2score==player1score){
                                gfx_text(750,20,"Deuce");
                        }
                        break;
        }

}
