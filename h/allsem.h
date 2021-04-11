/*
 * allsem.h
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#ifndef ALLSEM_H_
#define ALLSEM_H_

#include "semaphor.h"
#include "List.h"

class Semaphore;
class KernelSem;
class Allsem{
	private:
	          struct Elem{
			  Semaphore *sem;
			  Elem *next;
			  Elem(Semaphore *s) { sem=s; next=0;}
			  };
			  Elem *head, *tail;
			  int size;

	public:
			  Allsem():size(0),head(0),tail(0) {}

			  ~Allsem() { delQueue(); }

			  void put(Semaphore *s);
			  void get(Semaphore *s); //takes first PCB form the list

			  int getSize();

			  void delQueue();
};


#endif /* ALLSEM_H_ */
