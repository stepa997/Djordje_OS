/*
 * kernsem.h
 *
 *  Created on: Aug 27, 2018
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "semaphor.h"
#include "allsem.h"
#include "List.h"

class KernelSem{

public:

KernelSem(int initValue, Semaphore *sem);
~KernelSem();
int wait(int toBlock);
void signal();
int value() { return val; }
static Allsem *sviSem;

void block();
void deblock();
List *blockedlist;

friend Allsem;


private:

 int val;
 Semaphore *mySem;
};



#endif /* KERNSEM_H_ */
