#include <LPC213x.h>
#include <math.h>
#include "ral_encoder.h"
#include "ral_odometry.h"

void Odometry_Init(struct* Pos P, int encoderChannelL, int encoderChannelR){
    if(P == NULL)
	P = (struct Pos*)malloc(sizeof(struct Pos));
    P->x = 0;
    P->y = 0;
    P->theta = 0.0;
    P->encoderChannelL = encoderChannelL;
    P->encoderChannelR = encoderChannelR;
    return;
};

void Odometry_Update(struct* Pos P){
    int LCount = Encoder_ReadBuffer(P->encoderChannelL);
    int RCount = Encoder_ReadBuffer(P->encoderChannelR);
    double LCONST = 2 * ENCODER_L_RADIUS * PI / ENCODER_COUNT; 
    double RCONST = 2 * ENCODER_R_RADIUS * PI / ENCODER_COUNT; 
    double LDistance = LCount * LCONST;
    double RDistance = RCount * RCONST;
    double delta_Distance = (LDistance + RDistance) / 2.0;
    P->x += delta_Distance * cos(P->theta * PI_180);
    P->y += delta_Distance * sin(P->theta * PI_180);
    P->theta -= (LDistance - RDistance) / ENCODER_DISTANCE * C180_PI;
    return;	
};

void Odometry_Set(struct* Pos P, double x, double y, double theta){
    P->x = x;
    P->y = y;
    P->theta = theta;
    return;
};
