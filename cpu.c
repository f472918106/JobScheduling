/* cpu.c */

#include <stdio.h>
#include "const.h"
#include "cpu.h"

void initcpu(Cputype *cpu, int policy)
{
	cpu->state = FREE;
	cpu->policy = policy;
	cpu->runningjob = NULL;

	cpu->busytime = cpu->freetime = 0;
	cpu->jobnumber = 0;
	cpu->turnaroundtime = 0;
	cpu->weightedturnaroundtime = 0.0;
}

void printcpu(Cputype *cpu)
{
	switch (cpu->policy) {
	case FCFS:
		printf("\nFCFS, ");
		break;
	case SJF:
		printf("\nSJF , ");
		break;
	case HRN:
		printf("\nHRN , ");
		break;
	default:
		printf("\nUnknown, ");
	}
	printf("busy=%4d, free=%4d, jobnumber=%3d, ", 
		cpu->busytime, cpu->freetime, cpu->jobnumber);
	printf("turnaround=%4d, wturnaround=%6.2f", 
		cpu->turnaroundtime, cpu->weightedturnaroundtime);
}
