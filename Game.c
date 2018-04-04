/*
 * Game.c
 *
 *  Created on: Mar 12, 2018
 *      Author: User
 */

#include "Game.h"
#define numOfBugs 6
struct star {

    uint8_t xpos;
    uint8_t ypos;
    uint8_t pre_xpos;
    uint8_t speed;
    uint8_t on;
    int sleepcount;
    int sleepMax;


} ;

typedef struct star star_t;




struct bullet {

    uint8_t xpos;
    uint8_t ypos;
    uint8_t pre_xpos;
    uint8_t speed;



} ;

typedef struct bullet bullet_t;



struct green_bug {

    uint8_t xpos;
    uint8_t ypos;
    uint8_t pre_xpos;
    uint8_t pre_ypos;
    uint8_t alive;
    uint8_t distination_x;
    uint8_t distination_y;
    uint8_t inTheTable;
    uint8_t isLast;



} ;

typedef struct green_bug green_bug_t;


static green_bug_t bugs_table[numOfBugs];
uint8_t bullet_flag = 0;
volatile uint8_t RXDataL, RXDataL_temp = 0;
#define MAX_stars 15
uint8_t life_bugs =0;
static star_t stars_table[MAX_stars];
uint8_t Zero[3]= {0x1F,0x11,0x1F};
uint8_t One[8]= {0,0,0x1F};
uint8_t Two[8]= {0x17,0x15,0x1d};
uint8_t Three[8]= {0x15,0x15,0x1F};
uint8_t Four[8]= {0x1C, 0x04,0x1F};
uint8_t Five[8]= {0x1d,0x15,0x17};
uint8_t Six[8]= {0x1F,0x15,0x17};
uint8_t Seven[8]= {0x10,0x10,0x1F};
uint8_t Eight[8]= {0x1F,0x15,0x1F};
uint8_t Nine[8]= {0x1D,0x15,0x1F};
uint8_t path_X[100] = {64,63,62,62,61,60,59,58,58,57,55,54,54,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,34,33,33,32,32,31,31,30,30,30,29,29,28,28};
uint8_t path_Y[100] = {35,35,35,36,36,36,37,37,38,38,39,39,40,40,41,41,41,42,42,43,43,43,43,43,44,43,43,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25};
int8_t galagaShips_starY = 50;
int8_t galagaShips_starX = 35;
uint8_t to_be_deleted_x, to_be_deleted_y;
int8_t galagaShips_starY_prev, galagaShips_starX_prev ;

uint32_t GalagaShip[72]= {     0,0,0,0,0X00FF6666,0,0,0,0,
                               0,0,0,0,0X00FF6666,0,0,0,0,
                               0,0,0,0x000000FF,0X00FF6666,0x000000FF,0,0,0,
                               0xFF0000,0,0,0X00FF6666,0X00FF6666,0X00FF6666,0,0,0xFF0000,
                               0xFF0000,0,0X00FF6666,0X00FF6666,0X00FF6666,0X00FF6666,0X00FF6666,0,0xFF0000,
                               0X00FF6666,0X00FF6666,0X00FF6666,0xFF0000,0X00FF6666,0xFF0000,0X00FF6666,0X00FF6666,0X00FF6666,
                               0X00FF6666,0X00FF6666,0,0xFF0000,0X00FF6666,0xFF0000,0,0X00FF6666,0X00FF6666,
                               0X00FF6666,0,0,0,0X00FF6666,0,0,0,0X00FF6666};

uint32_t GreenBug [25] = {0x0000994C,0,0,0,0x0000994C,
                          0x0000994C,0x00FFFF00,0x00FFFF00,0x00FFFF00,0x0000994C,
                          0,0X00FF00FF,0x00FFFF00,0X00FF00FF,0,
                          0x0000994C,0x00FFFF00,0X00FF00FF,0x00FFFF00,0x0000994C,
                          0x0000994C,0,0x00FFFF00,0,0x0000994C,};



uint32_t Fire1 [25] = {0,0x00FF1100,0,0x00FF1100,0,
                       0x00FF1100,0x00FF3300,0x00FF3300,0x00FF3300,0x00FF1100,
                       0,0x00FF3300,0,0x00FF3300,0,
                       0x00FF1100,0x00FF3300,0x00FF3300,0x00FF3300,0x00FF1100,
                       0,0x00FF1100,0,0x00FF1100,0};


uint32_t Fire2 [25] = {0,0,0x00FF1100,0,0,
                       0,0x00FF1100,0x00FF3300,0x00FF1100,0,
                       0x00FF1100,0x00FF3300,0,0x00FF3300,0x00FF1100,
                       0,0x00FF1100,0x00FF3300,0x00FF1100,0,
                       0,0,0x00FF1100,0,0,};

uint32_t Fire3 [25] = {0,0,0,0,0,
                       0,0,0x00FF3300,0,0,
                       0,0x00FF3300,0x00FF3300,0x00FF3300,0,
                       0,0,0x00FF3300,0,0,
                       0,0,0,0,0,};

void LM_Text(uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint32_t charColor)
{
    uint8_t* tempAscii;

    switch(ASCI){

    case 0:

        tempAscii = Zero;
        break;
    case 1:

        tempAscii = One;
        break;
    case 2:

        tempAscii = Two;
        break;
    case 3:

        tempAscii = Three;
        break;
    case 4:

        tempAscii = Four;
        break;
    case 5:

        tempAscii = Five;
        break;
    case 6:

        tempAscii = Six;
        break;
    case 7:

        tempAscii = Seven;
        break;
    case 8:

        tempAscii = Eight;
        break;
    case 9:

        tempAscii = Nine;
        break;

    }

    int Index = 0;

    for (int i = Xpos; i < Xpos+3; i++){
        int shift = 2;
        for (int j = Ypos ; j< Ypos+7; j++){
            //  tempZero =Zero[Index]>> (7 - shift) & 0x01 == 0x01;
            //tempZero2 =Zero[Index];

            if (tempAscii[Index]>> (7 - shift) & 0x01 == 0x01 ){

                bufferBlue[i+(j*64)] = charColor  & 0xFF;
                bufferGreen[i+(j*64)] =( charColor >> 8 ) & 0xFF;
                bufferRed[i+(j*64)] =(charColor >> 16 ) &0xFF;

            }
            shift++;
        }

        Index++;
    }

}



void out_image(uint32_t* image, uint8_t Xpos, uint8_t Ypos, uint8_t whidth, uint8_t hight){

    int Index = 0;

    for (int i = Xpos; i < Xpos+whidth; i++){

        for (int j = Ypos ; j< Ypos+hight; j++){




            bufferBlue[j+(i*64)] = image[Index]  & 0xFF;
            bufferGreen[j+(i*64)] =( image[Index] >> 8 ) & 0xFF;
            bufferRed[j+(i*64)] =(image[Index] >> 16 ) &0xFF;

            Index++;
        }


    }

}

//*****************************************************************************
void displayBackground(){

    int j = 0;
    for (int i = 0 ; i < MAX_stars ; i+=4){
        j++;
        stars_table[i].on = 1;
        stars_table[i].sleepMax  = 20;
        stars_table[i].ypos = i*3 + 13;
        stars_table[i].xpos = j * 14;
        stars_table[i].sleepcount = 0;
        stars_table[i].speed = 1;


    }
    j = 0;

    for (int i = 1 ; i < MAX_stars ; i+=3){
        j++;
        stars_table[i].on = 1;
        stars_table[i].sleepMax  = 40;
        stars_table[i].ypos = i*3 + 13;
        stars_table[i].xpos = j * 18;
        stars_table[i].sleepcount = 0;
        stars_table[i].speed = 2;


    }

    j = 0;

    for (int i =2  ; i < MAX_stars ; i+=3){
        j++;
        stars_table[i].on = 1;
        stars_table[i].sleepMax  = 60;
        stars_table[i].ypos = i*3 + 13;
        stars_table[i].xpos = j * 42;
        stars_table[i].sleepcount = 0;
        stars_table[i].speed = 1;


    }




    while (1){


        for (int i = 0 ; i < MAX_stars; i++){

            stars_table[i].sleepcount++;
            if (stars_table[i].xpos > 63 ) stars_table[i].xpos  -=63;


            if (stars_table[i].on == 1  ){


                bufferBlue[stars_table[i].ypos+(stars_table[i].pre_xpos*64)] = 0;
                bufferGreen[stars_table[i].ypos+(stars_table[i].pre_xpos*64)] =0;
                bufferRed[stars_table[i].ypos+(stars_table[i].pre_xpos*64)] =0;


                if ( bufferGreen[stars_table[i].ypos+(stars_table[i].xpos*64) ]== 0 &&  bufferBlue[stars_table[i].ypos+(stars_table[i].xpos*64) ]== 0 &&  bufferRed[stars_table[i].ypos+(stars_table[i].xpos*64) ]== 0){
                    bufferBlue[stars_table[i].ypos+(stars_table[i].xpos*64)] = 10;
                    bufferGreen[stars_table[i].ypos+(stars_table[i].xpos*64)] =10;
                    bufferRed[stars_table[i].ypos+(stars_table[i].xpos*64)] =10;
                    if (stars_table[i].sleepMax == stars_table[i].sleepcount)  {
                        stars_table[i].sleepcount = 0;
                        stars_table[i].on == 0;


                    }

                    stars_table[i].pre_xpos =stars_table[i].xpos;
                }






            }
            else
            {

                if (stars_table[i].sleepMax == stars_table[i].sleepcount)  {
                    stars_table[i].sleepcount = 0;
                    stars_table[i].on == 1;

                }
            }

            stars_table[i].xpos += stars_table[i].speed;


        }


        G8RTOS_OS_Sleep(50);

    }
}

void moveGlagaShip(){

    uint8_t byte;
    // RXDataL_temp = RXDataL;
    while(1){


        G8RTOS_WaitSemaphore(&XpData);


        byte = RXDataL;

        G8RTOS_SignalSemaphore(&XpData);

        if ( get_bit(1, byte) == 0x01) galagaShips_starX++;
        if (galagaShips_starX >=52) galagaShips_starX = 52;
        if ( get_bit(0, byte) == 0x01) galagaShips_starX--;
        if (galagaShips_starX <=12) galagaShips_starX = 12;
        if ( get_bit(3, byte) == 0x01) galagaShips_starY++;
        if (galagaShips_starY >=52) galagaShips_starY = 52;
        if ( get_bit(2, byte) == 0x01) galagaShips_starY--;
        if (galagaShips_starY <=0) galagaShips_starY = 0;

        add_rectangle( 0, galagaShips_starX_prev, galagaShips_starX_prev+10, galagaShips_starY_prev, galagaShips_starY_prev+10);
        out_image(GalagaShip, galagaShips_starY,galagaShips_starX, 8, 9);

        galagaShips_starY_prev = galagaShips_starY;
        galagaShips_starX_prev = galagaShips_starX;

        G8RTOS_OS_Sleep(40);
    }

}

uint8_t get_bit(uint8_t shift, uint8_t byte){


    return (byte >> shift) & 0x01;
}


void   ReceiveUART2(){

    int i;

 while(1) {
        i++;
        G8RTOS_OS_Sleep(100);
    }
}


void  ReceiveUART()
{
    //    while(UCA3STATW & UCBUSY);
    //    RXDataH = MAP_UART_receiveData(EUSCI_A3_BASE);
    while(1){

        //  G8RTOS_WaitSemaphore(&XpData);
 int i;
 i++;

        RXDataL = MAP_UART_receiveData(EUSCI_A3_BASE);

     //   while(UCA3STATW);
        if (((RXDataL & 0b00010000) == 0b00010000 || (RXDataL & 0b00100000) == 0b00100000 ) && bullet_flag == 0 ){
            bullet_flag = 1;
        }
        //  G8RTOS_SignalSemaphore(&XpData);

        // return RXDataL;

        G8RTOS_OS_Sleep(75);
    }
}


void add_rectangle(int color, uint8_t x_start,uint8_t x_end, uint8_t y_start ,uint8_t y_end){



    for (int i= y_start; i< y_end ; i++ ){
        //
        for (int j =x_start; j < x_end ; j++){
            //
            //  if ( i >= x_start &&  i < x_end && j >= y_start &&  j < y_end  ){
            //  if(cube[k] > 5)  {
            bufferBlue[j+(i*64)] = color  & 0xFF;
            bufferGreen[j+(i*64)] =( color >> 8 ) & 0xFF;
            bufferRed[j+(i*64)] =(color >> 16 ) &0xFF;

        }
    }
}

void listenForBullets(){


    while(1){

        if (bullet_flag == 1) {


            G8RTOS_AddThread(&move_bullet, "move_bullet", 1);
            bullet_flag = 0;

        }
        G8RTOS_OS_Sleep(500);
    }

}


void move_bullet(){


    bullet_t b;
    b.ypos = galagaShips_starX+4;
    b.xpos = galagaShips_starY;

    while(1){


        out_bullet(b.pre_xpos,b.ypos, 0,0,0 );
        out_bullet(b.xpos,b.ypos, 0xFF,0x50,0 );


        b.pre_xpos =    b.xpos ;

        if (b.xpos == 2){

            out_bullet(b.xpos,b.ypos, 0,0,0 );

            G8RTOS_KillSelf();
            while(1);
        }

        check_bullet_collision(b.xpos, b.ypos );

        b.xpos--;

        G8RTOS_OS_Sleep(30);
    }
}

void out_pixel(uint8_t xpos, uint8_t ypos,  uint8_t red, uint8_t green, uint8_t blue  ){

    bufferBlue[ypos+(xpos *64)] = blue;
    bufferGreen[ypos+(xpos *64)] =green;
    bufferRed[ypos+(xpos *64)] =red;


}

void add_greenBugs(){


    uint8_t yOffset = 5;
    uint8_t xOffset = 5;


    while(1){
        yOffset = 5;
        xOffset = 5;
        if (life_bugs == 0){

            life_bugs = numOfBugs;

            for (int i = 0; i < numOfBugs; i++){

                bugs_table[i].distination_x = xOffset;
                bugs_table[i].distination_y = 20  + yOffset;
                yOffset += 7;

                if (i == 2){
                    yOffset = 8;

                    xOffset = 12;

                }

                if (i == 4){
                    yOffset = 11;

                    xOffset = 19;
                    G8RTOS_AddThread(&enemies_updater, "enemies_updater", 1);

                }


                G8RTOS_AddThread(&move_greenBug, "move_greenBug", 1);
                G8RTOS_OS_Sleep(300);
            }

        }

        G8RTOS_OS_Sleep(1000);

    }

}


void move_greenBug() {
    int path_index=0;
    uint8_t isEntring =1;
    uint8_t prev_xpos,  prev_ypos, xpos, ypos ;
    prev_ypos = path_Y[path_index]-5;
    prev_xpos = path_X[path_index]-5;
    int i=0;
    while(bugs_table[i].alive == 1){
        i++;
    }
    bugs_table[i].alive =1;
    // bugs_table[i].xpos = 10;
    //bugs_table[i].ypos = 40;

    //    uint8_t bug_xpos = 30;
    //    uint8_t bug_ypos = 40;
    //    uint8_t bug_prev_xpos;
    //    uint8_t bug_prev_ypos;


    while(1){

        if(bugs_table[i].alive == 0){


            out_exposion( bugs_table[i].ypos,  bugs_table[i].xpos);
            add_rectangle( 0, bugs_table[i].xpos, bugs_table[i].xpos+5, bugs_table[i].ypos, bugs_table[i].ypos+5);
            life_bugs--;
            G8RTOS_KillSelf();
            while(1);

        }

        //out_image(GreenBug, bugs_table[i].xpos, bugs_table[i].ypos, 5,5);
        if (isEntring == 1){

            bugs_table[i].ypos =  path_Y[path_index]-5;
            bugs_table[i].xpos =  path_X[path_index]-5;

            add_rectangle(0, prev_xpos, prev_xpos+5, prev_ypos, prev_ypos+5);
            out_image(GreenBug,bugs_table[i].ypos,  bugs_table[i].xpos, 5,5);
            prev_ypos =  bugs_table[i].ypos;
            prev_xpos =  bugs_table[i].xpos;
            path_index++;
            if(path_index == 46){
                //xpos = path_X[path_index -1]-5;
                // ypos = path_Y[path_index -1]-5;
                isEntring = 0;
            }
        } else
        {

            if (bugs_table[i].ypos !=  bugs_table[i].distination_x ){


                // out_exposion( bugs_table[i].xpos,  bugs_table[i].ypos);

                bugs_table[i].ypos--;
            }

            if (bugs_table[i].xpos !=  bugs_table[i].distination_y  ){


                // out_exposion( bugs_table[i].xpos,  bugs_table[i].ypos);


                if (bugs_table[i].xpos > bugs_table[i].distination_y )  bugs_table[i].xpos--;
                if (bugs_table[i].xpos <  bugs_table[i].distination_y )  bugs_table[i].xpos++;

            }

            //  if (bugs_table[i].xpos ==  bugs_table[i].distination_y &&  bugs_table[i].ypos ==  bugs_table[i].distination_x )  bugs_table[i].inTheTable = 1;


            add_rectangle( 0, prev_xpos, prev_xpos+5, prev_ypos, prev_ypos+5);
            out_image(GreenBug, bugs_table[i].ypos, bugs_table[i].xpos, 5,5);

            prev_xpos = bugs_table[i].xpos;
            prev_ypos = bugs_table[i].ypos;



        }

        G8RTOS_OS_Sleep(35);
    }


}

void out_bullet(uint8_t xpos, uint8_t ypos,  uint8_t red, uint8_t green, uint8_t blue){

    out_pixel(xpos,ypos, red,green,blue);
    out_pixel(xpos-1,ypos,red,green,blue);
    out_pixel(xpos+1,ypos,red,green,blue);
    out_pixel(xpos,ypos-1, red,green,blue);
    out_pixel(xpos,ypos+1, red,green,blue);

}


void  check_bullet_collision(uint8_t xpos, uint8_t ypos ){


    // if (bufferBlue[ypos+(xpos *64)] > 0 || bufferBlue[ypos+(xpos *64)] > 0 || bufferBlue[ypos+(xpos *64)] > 0){

    for (int i = 0 ; i < numOfBugs ; i++){

        if (bugs_table[i].alive == 1){

            if ((xpos - bugs_table[i].ypos < 5)  && ypos >  bugs_table[i].xpos -1 &&  ypos  <   bugs_table[i].xpos + 5   ){


                bugs_table[i].alive = 0;
                out_bullet(xpos,ypos, 0,0,0 );

                G8RTOS_KillSelf();
                while(1);
            }
        }
        //}


    }



}

void out_exposion(uint8_t xpos, uint8_t ypos){

    out_image(Fire3, xpos, ypos, 5,5);
    G8RTOS_OS_Sleep(150);
    out_image(Fire2, xpos, ypos, 5,5);
    G8RTOS_OS_Sleep(150);
    out_image(Fire1, xpos, ypos, 5,5);
    G8RTOS_OS_Sleep(150);
    out_image(Fire2, xpos, ypos, 5,5);
    G8RTOS_OS_Sleep(150);
    out_image(Fire3, xpos, ypos, 5,5);
    G8RTOS_OS_Sleep(150);



}

void enemies_updater(){

    uint8_t direction = 0;
    uint8_t counter = 0;

    while (1){

        if (life_bugs == 0){

            G8RTOS_KillSelf();
            while(1);
        }

        if (direction == 0 ) {

            if (counter < 10){
                counter++;
                for (int i = 0; i < numOfBugs ; i++){
                    //   if(bugs_table[i].inTheTable == 1)
                    bugs_table[i].distination_y--;



                }

                //                if (bugs_table[1].distination_y - bugs_table[0].distination_y  < 8 ) bugs_table[1].distination_y  = bugs_table[0].distination_y + 8;
                //                if (bugs_table[2].distination_y - bugs_table[1].distination_y  < 8 ) bugs_table[2].distination_y  = bugs_table[1].distination_y + 8;
                //                if (bugs_table[4].distination_y - bugs_table[3].distination_y  < 8 ) bugs_table[4].distination_y  = bugs_table[3].distination_y + 8;

            } else
            {
                counter = 0;
                direction = 1;
            }
        }
        else
        {
            if (counter < 10){
                counter++;
                for (int i = 0; i < numOfBugs ; i++){
                    //  if(bugs_table[i].inTheTable == 1)
                    bugs_table[i].distination_y++;

                }

                //                            if (bugs_table[1].distination_y - bugs_table[0].distination_y  > 8 ) bugs_table[1].distination_y  = bugs_table[0].distination_y + 8;
                //                            if (bugs_table[2].distination_y - bugs_table[1].distination_y  > 8 ) bugs_table[2].distination_y  = bugs_table[1].distination_y + 8;
                //                            if (bugs_table[4].distination_y - bugs_table[3].distination_y  > 8 ) bugs_table[4].distination_y  = bugs_table[3].distination_y + 8;

            } else
            {
                counter = 0;
                direction = 0;
            }

        }


        G8RTOS_OS_Sleep(100);

    }


}