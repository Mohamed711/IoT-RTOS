/* queue.c - enqueue, dequeue */
#include "headers.h"


/*------------------------------------------------------------------------
 * enqueue - Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
s32   enqueue(
          s32         pid,            /* ID of process to insert      */
          s16         q               /* ID of queue to use           */
        )
{
        s16   tail, prev;             /* Tail & previous node indexes */
        if (isbadqid(q) ||
        		isbadpid(pid))
        {
                return SYSERR;
        }
        tail = queuetail(q);
        prev = queuetab[tail].qprev;
        queuetab[pid].qnext  = tail;    /* Insert just before tail node */
        queuetab[pid].qprev  = prev;
        queuetab[prev].qnext = pid;
        queuetab[tail].qprev = pid;
        return pid;
}
/*------------------------------------------------------------------------
 * dequeue - Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
s32   dequeue(
          s16         q               /* ID queue to use              */
        )
{
        s32   pid;                    /* ID of process removed        */
        if (isbadqid(q)) {
                return SYSERR;
        } else if (isempty(q)) {
                return EMPTY;
        }
        pid = getfirst(q);
        queuetab[pid].qprev = EMPTY;
        queuetab[pid].qnext = EMPTY;
        return pid;
      }

sysCall	insert(
pid32		pid,		/* ID of process to insert	*/
qid16		q,		/* ID of queue to use		*/
s32		key		/* Key for the inserted process	*/
)
{
	s16	curr;			/* Runs through items in a queue*/
	s16	prev;			/* Holds previous node index	*/

	if (isbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	curr = firstid(q);
	while (queuetab[curr].qkey >= key) {
		curr = queuetab[curr].qnext;
	}

	/* Insert process between curr node and previous node */

	prev = queuetab[curr].qprev;	/* Get index of previous node	*/
	queuetab[pid].qnext = curr;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[curr].qprev = pid;
	return OK;
}

qid16 newqueue(void)
{
	static qid16 nextqid = NPROC; /* Next list in queuetab to use */
	qid16 q; /* ID of allocated queue */
	q = nextqid;
	if (q > NQENT) { /* Check for table overflow */
		return SYSERR;
	}
	nextqid += 2; /* Increment index for next call*/
	/* Initialize head and tail nodes to form an empty queue */
	queuetab[queuehead(q)].qnext = queuetail(q);
	queuetab[queuehead(q)].qprev = EMPTY;
	queuetab[queuehead(q)].qkey = MAXKEY;
	queuetab[queuetail(q)].qnext = EMPTY;
	queuetab[queuetail(q)].qprev = queuehead(q);
	queuetab[queuetail(q)].qkey = MINKEY;
	return q;
}

