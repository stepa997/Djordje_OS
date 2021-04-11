/*
 * timer.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#include "timer.h"
#include "PCB.h"
#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.h"
#include "Idle.h"
#include "thread.h"
#include "List.h"




static pInterrupt OldR;
int tss,tsp,tbp;
unsigned oldTimerOFF, oldTimerSEG;
extern void tick();

void interrupt timer(...){

	lock();
	//cout<<"usao u timer\n";
	unlock();
	if (!PCB::swReq && PCB::counter>0) {
		if (((PCB *)PCB::running)->getTslice()!=0) 
			PCB::counter--;
		//#ifndef BCC_BLOCK_IGNORE
		//#define BCC_BLOCK_IGNORE
		asm int 60h;
		//#endif BCC_BLCOK_IGNORE
		tick();
		if(PCB::sleepque->head!=0){
			PCB::sleepque->decrease();
			while(PCB::sleepque->head!=0 && PCB::sleepque->head->timesleep==0){
				Scheduler::put((PCB*)PCB::sleepque->get());
			}
		}

	}

	if (PCB::swReq || (PCB::counter == 0 && ((PCB *)PCB::running)->getTslice()!=0)) {

		//#ifndef BCC_BLOCK_IGNORE
		//#define BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		//#endif BCC_BLOCK_IGNORE
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		if (PCB::running->st!=idle && !((PCB *)PCB::running)->isDone() && !((PCB *)PCB::running)->isBlocked()) 
			Scheduler::put((PCB*)PCB::running);

		PCB::running=Scheduler::get();
		if(PCB::running==PCB::mainPCB) {
			lock(); 
			//cout<<"OPET MAIN\n"; 
			unlock();
		}
		if (PCB::running==0) {
			PCB::running=PCB::idlePCB; 
			lock(); 
			//cout<<"IDLE"; 
			unlock();
		}


		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		PCB::counter = PCB::running->getTslice();
				
		//#ifndef BCC_BLOCK_IGNORE
		//#define BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp,tbp
		}
		//#endif BCC_BLOCK_IGNORE
		if(PCB::swReq==1) 
			PCB::swReq=0;
	}
}


void inic(){

	lock();
	Idle* idlethr=new Idle();
	PCB::idlePCB = idlethr->myPCB;
	//#ifndef BCC_BLOCK_IGNORE
	//#define BCC_BLOCK_IGNORE
	OldR=getvect(0x08);
	setvect(0x08, timer);
	setvect(0x60, OldR);
	//#endif
	unlock();

}

void restore(){
	lock();
	//#ifndef BCC_BLOCK_IGNORE
	//#define BCC_BLOCK_IGNORE
	setvect(0x08, getvect(0x60));
	//#endif
	Thread* t = PCB::idlePCB->myThread;
	delete t;
	t = 0;
	PCB::idlePCB = 0;

	/*Thread* thread=PCB::mainPCB->myThread;
	if(thread != 0)
	 	delete thread;
	thread = 0;
	PCB::mainPCB=0;*/
	unlock();
}
