#ifndef __RAL_PID_H
#define __RAL_PID_H

#define MAX_PID_CHANNEL	10

struct PIDStruct{
	double kp,ki,kd,imax,tolerance,error_cumu,last_error;
	double (*err_Calc)(void* info);
	void (*output_Func)(void* info, double err);
	void* info;
	char start;
	double error_term;
	double PIDResult;
};

struct PosInfo{
	double acceleration;
	double top_speed;
	double deceleration;
	int target_pos;
	int time;
	int T1,T2,T3;
	int region;
	int pwmChannel;
	int encoderChannel;	
};

float PosInfoErrCal(const struct PosInfo*);

struct VelInfo{
	double target_speed;
	int old_pos;
	int pwmChannel;
	int encoderChannel;
};

float VelInfoErrCal(const struct VelInfo*);

struct ThetaInfo{
	double target_Theta;
	struct PosInfo* pos;
};

float ThetaInfoErrCal(const struct ThetaInfo*);

struct PIDStruct* PID_Init(struct PIDStruct* PIDS,double (*err_Calc)(void* info),void (*output_Func)(void* info, double err),void *info);
void PID_SetParameter(struct PIDStruct* PIDS,double kp,double ki,double kd,double imax,double tolerance);
double PID_Calc(struct PIDStruct* PIDS);
void PID_Update(struct PIDStruct* PIDS);
void PID_Start(struct PIDStruct* PIDS);
void PID_Stop(struct PIDStruct* PIDS);
void PID_Push(struct PIDStruct* PIDS);
void PID_UpdateAll(void);
#endif
