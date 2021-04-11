/*
 * Event.cpp
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo){
	myImpl = new KernelEv(ivtNo);
}

Event::~Event(){
	if (myImpl) delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
