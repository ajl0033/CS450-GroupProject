#ifndef _IOCB_H
#define _IOCB_H

#include <system.h>
#include "PCB.h"
enum status {NOTHING, READING, WRITING};

typedef struct dcb{

//indicates if open or closed
  int open;

//indicates completion of operation
//0 at beginning of operation, 1 at end.
  int events;

  enum status status;

//Input buffer
//Stores info from device requested by application
  unsigned char* in;
  int in_x; //current index
  int in_s; //size of 'in' buffer

//output buffer
//stores info FOR device supplied by application
  unsigned char* out;
  int out_x; //current index
  int out_s; //size of out buffer
  int out_count;

//Rign buffer
//Written to whenever the device triggers an interupt
  unsigned char ring[16];
  int ring_inx;
  int rign_outx;
  int ring_s;
} dcb;

typedef struct iocb{
  int count;
  PCB *pcb;
  dcb *dcb;
  int events;
  enum status status;
  struct iocb *next;
  struct iocb *previous;

} iocb;

typedef struct iqueue {
    int count;
    iocb *head;
    iocb *tail;
} iqueue;




#endif