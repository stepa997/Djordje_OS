/*
 * PCB.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "List.h"
#include "SCHEDULE.h"
#include <DOS.H>
#include "sleepque.h"

int PCB::posId=0;
List* PCB::lista = new List();
PCB* PCB::running=0;
PCB* PCB::idlePCB=0;
int PCB::swReq=0;
int PCB::counter=0;
PCB* PCB::mainPCB=0;
SleepQue* PCB::sleepque=new SleepQue();


PCB::PCB(StackSize stackS, Time timeS, Thread* thread) {
	// TODO Auto-generated constructor stub
	if (stackS>65535) stackS=65535;
	   stackSize=stackS/sizeof(unsigned);
	timeSlice=timeS;
	myThread=thread;
	id=++posId;

	waiting = new List();
	lista->put(this);

	st=newthr;
	bp=0;
	sp=0;
	ss=0;
	stack=0;

}

void PCB::createStack(){

	st=ready;

	stack=new unsigned[stackSize];

	stack[stackSize-1]=0x200;
		  #ifndef BCC_BLOCK_IGNORE
	#define BCC_BLOCK_IGNORE
		  ss=FP_SEG(stack+stackSize-12);
		  sp=FP_OFF(stack+stackSize-12);
		  stack[stackSize-2]=FP_SEG(&(PCB::wrapper));
		  stack[stackSize-3]=FP_OFF(&(PCB::wrapper));
	#endif
	  bp=sp;

	  Scheduler::put(this);
}

void PCB::wrapper(){
	PCB::running->myThread->run();
	PCB::running->st=done;
	PCB::running->clearAll();
	dispatch();
}

int PCB::isDone() {
	return st==done;
}

int PCB::isBlocked(){
	return st==blocked;
}

Time PCB::getTslice(){
	return timeSlice;
}

void PCB::clearAll(){
	lock();
		while(waiting->size!=0){
			PCB* p = waiting->get();
			p->st = ready;
			Scheduler::put(p);
		}
		unlock();
}

PCB::~PCB() {
	// TODO Auto-generated destructor stub
	 if (stack) delete [] stack;
	 if (waiting) delete waiting;
}

void PCB::sleep(Time timeToSleep){
	lock();
	PCB::running->st=blocked;
	sleepque->putsleep((PCB*)(PCB::running), timeToSleep);
	unlock();
	dispatch();
}
