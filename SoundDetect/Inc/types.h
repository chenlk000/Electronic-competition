#ifndef _TYPES_H_
#define _TYPES_H_

#define NULL 0
//#define PI 3.14159265358979323846
#define FPGA_SYSTEM_TICK 200000000.0
#define FLASH_RETRY_TIMES 5
#define FLASH_RETRY_INTERVAL 800

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef enum
{
    F_FAILED = -1,
    F_SUCCESS = 0,
} FUNCTION_RETURN;

typedef enum
{
    L_FALSE = 0,
    L_TRUE = 1,
} LOGICAL_ENUM;

typedef enum
{
    APP_MAIN,
    APP_CORE,
    APP_MODEM,
    TASK_NUM
} TASK_ENUM;

//typedef enum
//{
//	MSG1_ARRIVE,
//	MSG2_ARRIVE,
//	MSG3_ARRIVE,
//	MSGALL_ARRIVE
//} MSG_RECEIVE;

typedef enum
{
    CORE_USART1_RECV,
    CORE_USART2_RECV,
    CORE_USART3_RECV,
    CORE_USART4_RECV,
    CORE_USART5_RECV,
    CORE_MSG_NUM
} CORE_MSG_ENUM;

typedef enum
{
    USART1_RECV,
    USART2_RECV,
    USART3_RECV,
    USART4_RECV,
    USART5_RECV,
    KEY_0_PRESS,
    KEY_0_RELEASE,
    KEY_1_PRESS,
    FEED_DOG,
    MSGALL_ARRIVE,
		MSGALL_ARRIVE_D,
    DSP_START,
    GET_MEASURE_DATA,
    TASK_MSG_NUM
} TASK_MSG_ENUM;

typedef enum
{
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
    TIMER_6,
    TIMER_7,
    TIMER_8,
    TIMER_9,
    TIMER_10,
    TIMER_11,
		TIMER_12,
		TIMER_13,
    TIMER_NUM
} TIMER_ENUM;

typedef struct
{
    float real;
    float imagin;
} Complex;

typedef struct
{
    u32 fre;
    Complex input;
    Complex output;
    Complex R;
} FPGA_RESULT;

typedef struct
{
    u8 cmd;
    u8 length;
    u8 data[];
} TASK_MSG;

typedef int (*MSG_PROC)(const TASK_MSG *msg);

typedef struct
{
    TASK_MSG_ENUM cmd;
    MSG_PROC pFun;
} TASK_MSG_MAP;

#endif //! _TYPES_H_
