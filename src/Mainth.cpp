/*
 * Mainth.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#include "Mainth.h"

Mainth* Mainth::Mainthread=0;

int userMain(int argc, char* argv[]);

Mainth::Mainth(int argc, char* argv[]):Thread() {
	// TODO Auto-generated constructor stub
	aargc=argc; aargv=argv; val=-1;
}

Mainth::~Mainth() {
	// TODO Auto-generated destructor stub
	waitToComplete();
}

void Mainth::run(){
	val=userMain(aargc, aargv);
}
