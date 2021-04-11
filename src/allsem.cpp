/*
 * allsem.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: OS1
 */

#include "allsem.h"

int Allsem::getSize(){
	return size;
}

void Allsem::put(Semaphore* s){
	lock();
	Elem* pom = new Elem(s);
	if(head==0) head=tail=pom;
	else{
		tail->next=pom;
		tail=pom;
	}
	size++;
	unlock();
}

void Allsem::get(Semaphore* sem){
	lock();
	Elem *tek = head, *pom = 0;

		while(tek->sem != sem  && tek != 0){
		     pom = tek;
		     tek = tek->next;
		}
		if(tek == 0)
			return;
		else
			if(tek == head)
				head = head->next;
			else
				pom->next = tek->next;

		if(tek->sem->val() < 0){               //pre nego sto se obrise moraju sve niti da se odblokiraju koje cekaju na njemu
	     int p = (-1)*tek->sem->val();
	     for(int i=0;i< p; i++)
			tek->sem->signal();
		}
		size--;
		delete tek;
		unlock();
}

void Allsem::delQueue(){
	lock();
	Elem* pom;
			while(head != 0){
				pom = head;
				if(pom->sem->val() < 0){           //ako je imalo blokiranih na semaforu onda se oslobode
				int p = (-1)*pom->sem->val();
				for(int i =0; i<p; i++)
					pom->sem->signal();
				delete pom;
				}
				head = head->next;
			}
			head = 0;
		    size = 0;
		    tail=0;
	unlock();
}


