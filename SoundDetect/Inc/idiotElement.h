#ifndef IDIOT
#define IDIOT
#define CMD_SIZE 15


char* cmd_write(short direction, short speed, short yaw, short time);
int cmdSend(char * cmd );

#endif
