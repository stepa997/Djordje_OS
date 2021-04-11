/*
 * Mainth.h
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#ifndef MAINTH_H_
#define MAINTH_H_

#include "Thread.h"


class Mainth : public Thread {
public:
	int val;
	int aargc;
	char** aargv;
	static Mainth* Mainthread;
	void run();
	Mainth(int argc, char* argv[] );
	~Mainth();
};

#endif /* MAINTH_H_ */
