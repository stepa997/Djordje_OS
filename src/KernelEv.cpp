/*
 * KernelEv.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTEntry.h"
#include "timer.h"
#include "SCHEDULE.H"
#include "allsem.h"
#include "List.h"

KernelEv::KernelEv(IVTNo ivtNo){
	num = ivtNo;
	val = 0; // nije blokiran
	IVTEntry::entries[num]->myEvent = this;
	create = (PCB*)PCB::running;
}

void KernelEv::wait(){
	if(create == PCB::running){
		lock();
		if(val == 0){
			create->st = blocked;
			val = 1;
			unlock();
			dispatch();
		}
		else 
			unlock();
	}
}

void KernelEv::signal(){
		lock();
		if(val == 1){ // ako je blokiran
			create->st = ready;
			Scheduler::put(create);
			val = 0;
		}
		unlock();
		//dispatch();
}

KernelEv::~KernelEv(){
	if (create->st == blocked){
			create->st = ready;
			Scheduler::put(create);
		}
		create = 0;
		delete IVTEntry::entries[num];
		IVTEntry::entries[num]=0;
}
