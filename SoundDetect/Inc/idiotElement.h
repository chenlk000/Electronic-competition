#ifndef IDIOT
#define IDIOT
#define CMD_SIZE 15
#define CONFIG_SIZE 7
#define GYRO_ON 1
#define GYRO_OFF 0

char* cmd_write(short direction, short speed, short yaw, short time);
char* config_write(short state);
int cmdSend(char * cmd,char length);

#endif
