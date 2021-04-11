/*
 * sleepque.h
 *
 *  Created on: Aug 29, 2018
 *      Author: OS1
 */

#ifndef SLEEPQUE_H_
#define SLEEPQUE_H_

#include "pcb.h"
#include "thread.h"

class SleepQue{
private:

	struct Elem{
		PCB* pcb;
		Time timesleep;
		Elem* sled;
		Elem(PCB* p, Time time) {pcb=p; sled=0; timesleep=time;}
	};

	Elem *tail;
	int size;
public:
	SleepQue():head(0),tail(0), size(0){};
	void putsleep(PCB* p, Time t);
	PCB* get();

	Elem * head;
	void decrease();
	int getSize();
	~SleepQue(){del();}

//	PCB *getbyID(ID id);
//	void remove(ID id);

	void del();

};



#endif /* SLEEPQUE_H_ */
