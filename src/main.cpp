/*
 * main.cpp
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */
#include "Mainth.h"
#include <IOSTREAM.H>
#include "PCB.h"
#include "timer.h"

int main(int argc, char** argv){

	cout<<"POCELO\n";

	inic();

	for(int i=0; i<32000; i++);

	PCB::running = new PCB(2024, 2, 0);
	PCB::running->st=ready;

	Mainth* mainth = new Mainth(argc,argv);
	mainth->start();

	delete mainth;

    restore();

	cout<<"KRAJ!";
return 0;
}

