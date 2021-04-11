/*
 * Idle.h
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class Idle: public Thread {
public:
	void start();
	virtual void run();
	Idle();
};

#endif /* IDLE_H_ */
