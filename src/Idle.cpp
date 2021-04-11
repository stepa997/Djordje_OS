/*
 * Idle.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#include "Idle.h"
#include "List.h"
#include <iostream.h>

Idle::Idle():Thread(4096,1) {
	// TODO Auto-generated constructor stub
	start();
}

void Idle::run(){
	while(1){
		//cout << "idle" << endl;
	}
}

void Idle::start(){
	lock();
		if(myPCB->st==newthr){
			myPCB->createStack();
			myPCB->st=idle;
		}
		unlock();
}
