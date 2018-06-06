/* handle.h */

#ifndef HANDLE
#define HANDLE

#include "event.h"

void jobcreateeventhandle(Eventtype *event);
void jobscheduleeventhandle(Eventtype *event);
void jobexiteventhandle(Eventtype *event);

#endif
