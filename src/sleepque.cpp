/*
 * sleepque.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#include "sleepque.h"
#include "List.h"

void SleepQue::putsleep(PCB* p, Time t){
	lock();
	Elem* curr, *prev=0, *pom;
	if(head==0) {
		curr = new Elem(p, t);
		head=tail=curr;
	}
	else{
		curr=head;
		while(t>curr->timesleep && curr!=0){
			t-=curr->timesleep;
			prev=curr;
			curr=curr->sled;
		}
		Elem* pom = new Elem(p, t);
		if(prev == 0){
			pom->sled= head;
			head=pom;
		}
		else{
			prev->sled=pom;
			pom->sled=curr;
		}
		if(pom->sled){
			pom->sled->timesleep-=t;
		}
	}

	curr=prev=pom=0;
	delete curr, prev, pom;
	size++;
	unlock();
}

PCB* SleepQue::get(){
	lock();
	if (head==0) return 0;

	Elem* pom = head;
	head=head->sled;
	if(head==0) tail=0;
	PCB* p = pom->pcb;
	size--;
	p->st=ready;
	unlock();
	return p;
}

int SleepQue::getSize(){
	return size;
}

void SleepQue::del(){
	while(head){
		Elem* pom=head; head=head->sled;
		delete pom;
	}
	tail=head=0; size=0;
}

void SleepQue::decrease(){
		head->timesleep-= 1;
}

