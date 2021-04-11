/*
 * timer.h
 *
 *  Created on: Sep 15, 2018
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "PCB.h"

typedef void interrupt (*pInterrupt) (...);

class PCB;
class Thread;
void interrupt timer(...);

void inic();
void restore();



#endif /* TIMER_H_ */
