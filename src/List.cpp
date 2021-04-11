/*
 * List.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: OS1
 */

#include "List.h"

List::List() {
	// TODO Auto-generated constructor stub
	first=0; last=0; size=0;
}

List::~List() {
	// TODO Auto-generated destructor stub
	del();
}

void List::del(){
	Elem* curr;
	while(first){
		curr=first;
		first=first->next;
		delete curr;
	}
}

void List::put(PCB* p){
	lock();
	Elem* curr = new Elem(p);
	if(first==0) first=last=curr;
	else{
		last->next=curr;
		last=last->next;
	}
	size++;
	curr=0;
	delete curr;
	unlock();
}

PCB* List::get(){
	lock();
	if (first==0) {unlock(); return 0;}
	else{
		Elem* curr=first;
		first=first->next;
		curr->next=0;
		size--;
		unlock();
		return curr->pcb;
	}
}
