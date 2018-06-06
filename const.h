/* const.h */

#ifndef CONST
#define CONST

#define MAXJOBCREATETIMEINTERVAL 50
#define NEXTJOBCREATETIMEINTERVAL (rand() % MAXJOBCREATETIMEINTERVAL + 1)
#define MAXJOBRUNTIME 100
#define NEXTJOBRUNTIME (rand() % MAXJOBRUNTIME + 1)

#define JOBBACKUPSTATE 	1
#define JOBRUNNINGSTATE 	2
#define JOBEXITSTATE 	3

#define BUSY 1
#define FREE 2

#define FCFS	1
#define SJF	2
#define HRN	3

#define JOBCREATEEVENT 		1
#define JOBSCHEDULEEVENT 	2
#define JOBEXITEVENT		3

typedef int Boolean;
#define FALSE 0
#define TRUE  1

#endif

