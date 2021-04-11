/*
 * List.h
 *
 *  Created on: Sep 14, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_


#include <DOS.H>
#include "PCB.h"

#define lock(){asm pushf; asm cli;}
#define unlock(){asm popf;}

class List {
private:
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB*p){
			pcb=p; next=0;
		}
	};
public:
	int size;
	Elem* first, *last;
	List();
	virtual ~List();
	void del();
	void put(PCB* p);
	PCB* get();

};

#endif /* LIST_H_ */
