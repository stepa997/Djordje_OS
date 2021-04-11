/*
 * Thread.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: OS1
 */

#include "Thread.h"
#include "List.h"
#include "PCB.h"
#include "timer.h"

Thread::Thread(StackSize stackSize, Time timeSlice) {
	// TODO Auto-generated constructor stub
	lock();
	myPCB = new PCB(stackSize, timeSlice, this);
	unlock();
}

void Thread::start(){
	lock();
	myPCB->createStack();
	unlock();
}

ID Thread::getId(){
	return myPCB->id;
}

ID Thread::getRunningId(){
	return PCB::running->id;
}

void Thread::waitToComplete(){
	lock();
	if(myPCB->st==newthr || myPCB==PCB::running || myPCB->st==done || myPCB==PCB::idlePCB){
		unlock();
		return;
	}
	PCB::running->st=blocked;
	myPCB->waiting->put((PCB*)PCB::running);
	unlock();
	dispatch();
}

Thread::~Thread() {
	// TODO Auto-generated destructor stub
	lock();
	delete myPCB;
	unlock();
}

void dispatch(){
	lock();
	PCB::swReq=1;
	timer();
	unlock();
}

void Thread::sleep(Time timeToSleep){
	if(PCB::running != PCB::idlePCB && timeToSleep != 0)
			((PCB*)PCB::running)->sleep(timeToSleep);
}
