// PCB Header
#include <system.h>

typedef struct PCB{
  char *processName;
  unsigned char *processClass;
  int priority;
  int state;
  int stateSuspended;
  unsigned char *stackTop;
  unsigned char *stackBase;
  struct PCB *nextPCB;
  struct PCB *previousPCB;
} PCB;

typedef struct queue {
    int count;
    PCB *head;
    PCB *tail;
} queue;

void fifo_enqueue (queue *q, PCB *pcb); // Emily

void priority_enqueue (queue *q, PCB *pcb);// Emily

PCB* AllocatePCB(); // Anthony

void FreePCB(); // Anthony

PCB* SetupPCB(char* processName, unsigned char processClass, int priority); // Jarett - its kinda funky cuz of processClass, stackTop, and stackBase

void FindPCB(char* processName); // Will

void InsertPCB(); // Emily

void RemovePCB(); // Emily

void CreatePCB(char* processName, unsigned char processClass, int priority); // Jarett

void DeletePCB(char* processName); //Will

void BlockPCB(char* processName); //Jarett

void UnblockPCB(char* processName);// these were all really similar

void SuspendPCB(char* processName);// and should be mostly right - I have to study for 422 tm

void ResumePCB(char* processName);//  cuz i have the quiz wednesday - I  can still hop on

void SetPCBPriority(char* processName, int priority);// and help but cant do to much - Hopefully this is a decent start

void ShowPCB(char* processName); // Will

void ShowReady(); // Will

void ShowBlocked(); // Will

void ShowAll(); // Will
