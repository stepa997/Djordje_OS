/*
 * PCB.h
 *
 *  Created on: Sep 14, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
#include "sleepque.h"

class List;
class Thread;
class SleepQue;
enum states {newthr,ready,blocked,done,idle};

class PCB {

public:

   static PCB *running;
   static PCB *mainPCB;
   static int counter;
   static int swReq;
   static List *lista;
   static SleepQue *sleepque;

   int state();

   ID getId();
   Time getTslice() ;

   void createStack();
   void sleep(Time timeToSleep);
   PCB(StackSize stacksSize, Time timeSlice, Thread *thread);


   static void wrapper();

   void clearAll () ;

   int isDone() ;
   int isBlocked() ;

   states st;
   static PCB* idlePCB;
   ~PCB();

   List *waiting;
   Thread *myThread;


   unsigned ss;
   unsigned sp;
   unsigned bp;
private:

   friend class Thread;

   static int posId;
   int id;



   unsigned  *stack;


   Time timeSlice;
   StackSize stackSize;




};


#endif /* PCB_H_ */
