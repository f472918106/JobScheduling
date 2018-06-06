/* handle.c */

#include <stdio.h>
#include "const.h"
#include "job.h"
#include "event.h"
#include "cpu.h"
#include "handle.h"

void jobcreateeventhandle(Eventtype *event)
{
	extern int jobid;
	extern int systemtime;
	extern Jobtype jobqueue;
	extern Eventtype eventqueue;
	extern Cputype cpu;

	Jobtype *job;
	Eventtype *e;

	if ((job = createjob((jobid++), systemtime, NEXTJOBRUNTIME)) == NULL)
		return;

	addjobtoqueue(job, &jobqueue);
	event->jobid = job->id;

	if (cpu.state == FREE) {
		e = createevent(systemtime, JOBSCHEDULEEVENT);
		frontaddeventtoqueue(e, &eventqueue);
	}

	return;
}

void jobscheduleeventhandle(Eventtype *event)
{
	extern Eventtype eventqueue;
	extern Jobtype jobqueue;
	extern int systemtime;
	extern Cputype cpu;

	Jobtype *job;
	Eventtype *e;

	if (isemptyjobqueue(&jobqueue) == TRUE)
		return;

	switch (cpu.policy) {
	case FCFS:
		job = firstjobinqueue(&jobqueue);
		break;
	case SJF:
		job = shortjobinqueue(&jobqueue);
		break;
	case HRN:
		job = hrnjobinqueue(&jobqueue);
		break;
	default:
		job = firstjobinqueue(&jobqueue);
		break;
	}
			
	removejobfromqueue(job);
	event->jobid = job->id;

	job->state = JOBRUNNINGSTATE;
	cpu.runningjob = job, cpu.state = BUSY;

	e = createevent(systemtime + job->runtime, JOBEXITEVENT);
	e->jobid = job->id;
	addeventtoqueue(e, &eventqueue);
	
	return;
}

void jobexiteventhandle(Eventtype *event)
{
	extern Cputype cpu;
	extern Jobtype jobqueue, exitjobqueue;
	extern int systemtime;
	extern Eventtype eventqueue;

	Jobtype *job;
	Eventtype *e;

	job = cpu.runningjob;
	job->state = JOBEXITSTATE, job->exittime = systemtime;
	job->turnaroundtime = job->exittime - job->createtime;
	job->weightedturnaroundtime = 
		(double) job->turnaroundtime / job->runtime;

	cpu.state = FREE, cpu.busytime += job->runtime;
	cpu.jobnumber++;

	addjobtoqueue(job, &exitjobqueue);
	
	if (isemptyjobqueue(&jobqueue) == FALSE) {
		e = createevent(systemtime, JOBSCHEDULEEVENT);
		frontaddeventtoqueue(e, &eventqueue);
	}

	return;		
}
