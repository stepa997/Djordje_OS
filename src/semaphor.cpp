/*
 * semaphor.cpp
 *
 *  Created on: Sep 16, 2018
 *      Author: OS1
 */

#include "semaphor.h"
#include "kernsem.h"

int Semaphore::val(){
	return myImpl->value();
}

Semaphore::Semaphore(int init){

	myImpl=new KernelSem(init,this);
}

Semaphore::~Semaphore(){

	delete myImpl;
}

int Semaphore::wait(int toBlock){

	return myImpl->wait(toBlock);
}

void Semaphore::signal(){

	myImpl->signal();
}

