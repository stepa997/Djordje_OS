/*
 * kernsem.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: OS1
 */

#include "kernsem.h"
#include "List.h"
#include "SCHEDULE.h"

Allsem* KernelSem::sviSem = new Allsem();

KernelSem::KernelSem(int i, Semaphore* sem){
	val=i;
	mySem=sem;
	sviSem->put(sem);
	blockedlist=new List();
}

KernelSem::~KernelSem(){
	lock();
	mySem=0;
	delete blockedlist;
	unlock();
}

int KernelSem::wait(int toBlock){
	lock();
	int ret = 0;
	if (!toBlock && val<=0){
		ret = -1;
		unlock();
	}
	else {
		if (--val<0) {
			ret = 1;
			block();
		}
		unlock();
		if(ret == 1)
			dispatch();
	}
	return ret;
}

void KernelSem::signal(){
	lock();
	if(val++<0) 
		deblock();
	unlock();
}

void KernelSem::block(){
	if(PCB::running!=PCB::idlePCB){
		PCB::running->st=blocked;
		blockedlist->put((PCB*)(PCB::running));
	}
}

void KernelSem::deblock(){
	PCB *pcb = blockedlist->get();
	pcb->st = ready;
	Scheduler::put(pcb);
}
