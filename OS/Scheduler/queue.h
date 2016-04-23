#ifndef QUEUE_H_
#define QUEUE_H_

#include "headers.h"

qid16 readylist;
qid16 suspendedlist;

//#define SYSERR (0);
#ifndef NQENT

#define NQENT   (NPROC + 4 + NSEM + NSEM)
#endif
#define EMPTY   (-1)            /* Null value for qnext or qprev index  */
#define MAXKEY  0x7FFFFFFF      /* Max key that can be stored in queue  */
#define MINKEY  0x80000000      /* Min key that can be stored in queue  */
struct  qentry  {               /* One per process plus two per list    */
	    s32   qkey;           /* Key on which the queue is ordered    */
        s16   qnext;          /* Index of next process or tail        */
        s16   qprev;          /* Index of previous process or head    */
};
extern  struct qentry   queuetab[];
/* Inline queue manipulation functions */
#define queuehead(q)    (q)
#define queuetail(q)    ((q) + 1)
#define firstid(q)      (queuetab[queuehead(q)].qnext)
#define lastid(q)       (queuetab[queuetail(q)].qprev)
#define isempty(q)      (firstid(q) >= NPROC)
#define nonempty(q)     (firstid(q) < NPROC)
#define firstkey(q)     (queuetab[firstid(q)].qkey)
#define lastkey(q)      (queuetab[ lastid(q)].qkey)
/* Inline to check queue id assumes interrupts are disabled */
#define isbadqid(x)     (((s32)(x) < 0) || (s32)(x) >= NQENT-1)


//APIs
inline s32 getitem(
s32         pid          /* ID of process to remove */
)
{
	s32   prev, next;
	next = queuetab[pid].qnext;  /* Following node in list  */
	prev = queuetab[pid].qprev;  /* Previous node in list   */
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;
	return pid;
}

inline s32 getfirst( s16 q )
{
	s32  head;
	if (isempty(q)) {
		return EMPTY;
	}
	head = queuehead(q);
	return getitem(queuetab[head].qnext);
}


inline s32 getlast(
s16         q               /* ID of queue from which to */
)                               /* Remove a process (assumed */
/*   valid with no check)    */
{
	s16 tail;
	if (isempty(q)) {
		return EMPTY;
	}
	tail = queuetail(q);
	return getitem(queuetab[tail].qprev);
}

s32   dequeue(s16 q);
s32   enqueue(s32 pid,s16 q );
sysCall	insert(pid32 pid, qid16 q, s32 key);
qid16 newqueue(void);

#endif
