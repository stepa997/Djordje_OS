/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#include "IVTEntry.h"
#include "KernelEv.h"
#include <dos.h>
#include "SCHEDULE.h"
#include "allsem.h"

IVTEntry* IVTEntry::entries[numOfEntries];

IVTEntry::IVTEntry(IVTNo ivtNoo, pInterrupt newroutine)
{
	oldRout=0;
	ivtNo=ivtNoo;
	myEvent=0;
#ifndef BCC_BLOCK_IGNORE
	lock();
	oldRout=getvect(ivtNo);
	setvect(ivtNo, newroutine);
	unlock();
#endif
	IVTEntry::entries[ivtNo]=this;
}

void IVTEntry::signal(){
	myEvent->signal();
}

IVTEntry::~IVTEntry()
{
#ifndef BCC_BLOCK_IGNORE
setvect(ivtNo,oldRout);
#endif
myEvent=0;
oldRout=0;
}

void IVTEntry::callOld(){
	(*oldRout)();
}
