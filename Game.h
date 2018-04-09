/*
 * Game.h
 *
 *  Created on: Mar 12, 2018
 *      Author: User
 */

#ifndef GAME_H_
#define GAME_H_
#include <stdint.h>
#include <driverlib.h>
#include "G8RTOS.h"

int tempZero,tempZero2;
uint8_t bufferBlue[4097],bufferGreen[4097],bufferRed[4097];
uint32_t buffer[4097];
uint8_t newFrame ;
semaphore_t XpData;
extern uint8_t scoreValue;
uint8_t RXData_Pi;

void writeScore(uint8_t score, int color);
void menu();
void outString(char *string, uint16_t Xpos, uint16_t Ypos, uint32_t charColor);
void LM_Text(uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint32_t charColor);
void out_image(uint32_t* image, uint8_t Xpos, uint8_t Ypos, uint8_t whidth, uint8_t hight);
void displayBackground();
uint8_t get_bit(uint8_t shift, uint8_t byte);
void ButtonsInit();
void writeLogo();
void moveGlagaShip();
void initUART_XBee();
void ReceiveUART_Pi();
void  ReceiveUART_XBee();
void move_bullet();
void IdleThread();
void LaunchApp();
void initUARTP3();
void initUART_XBee();
void output_frame();
void listenForBullets();
void out_pixel(uint8_t xpos, uint8_t ypos,  uint8_t red, uint8_t green, uint8_t blue  );
void add_rectangle(int color, uint8_t x_start,uint8_t x_end, uint8_t y_start ,uint8_t y_end);
void out_bullet(uint8_t xpos, uint8_t ypos,  uint8_t red, uint8_t green, uint8_t blue);
void move_greenBug();
void add_greenBugs();
void  check_bullet_collision(uint8_t xpos, uint8_t ypos );
void out_exposion(uint8_t xpos, uint8_t ypos);
void enemies_updater();

void menuListener();

#endif /* GAME_H_ */
