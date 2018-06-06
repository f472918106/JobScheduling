/* cpu.h */

#ifndef CPU
#define CPU

#include "job.h"

typedef struct Cpu {
	int state;
	int policy;
	Jobtype *runningjob;

	int busytime;
	int freetime;
	int jobnumber;
	int turnaroundtime;
	double weightedturnaroundtime;

} Cputype;

void initcpu(Cputype *cpu, int policy);
void printcpu(Cputype *cpu);

#endif


