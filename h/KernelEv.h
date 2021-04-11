/*
 * KernelEv.h
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "PCB.h"
#include "Event.h"

class Event;
class KernelEv {
public:
	KernelEv(IVTNo ivtNo);
		void wait ();
		void signal();
		virtual ~KernelEv ();
	protected:
		friend class Event;
	private:
		IVTNo num;
		int val;
		PCB* create;
};

#endif /* KERNELEV_H_ */
