/*
 * Event.h
 *
 *  Created on: Sep 17, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;
class Event {
public:
	Event (IVTNo ivtNo);
	 ~Event ();
	 void wait ();
	protected:
	 friend class KernelEv;
	 void signal(); // can call KernelEv
	private:
	 KernelEv* myImpl;
};


#define PREPAREENTRY(number, flag)\
		void interrupt inter##number(...);\
		IVTEntry newEntry##number(number, inter##number);\
		void interrupt inter##number(...) {\
			if (flag == 1) \
				newEntry##number.callOld();\
			newEntry##number.signal();\
		}\

#endif /* EVENT_H_ */
