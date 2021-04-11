/*
 * IVTEntry.h
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

class KernelEv;

#include "timer.h"


typedef unsigned char IVTNo;

const int numOfEntries=256;

class IVTEntry {
public:

	IVTEntry(IVTNo ivtNo, pInterrupt irout);
	~IVTEntry();

	void signal();

	void callOld();
	static IVTEntry* entries[numOfEntries];
	friend class KernelEv;

	private:
		 IVTNo ivtNo;
	     KernelEv *myEvent;
	     pInterrupt oldRout;
};

#endif /* IVTENTRY_H_ */
