

#include "os.h"

CPU_STK *OSTaskStkInit (OS_TASK_PTR p_task, void *p_arg, CPU_STK* base, CPU_STK* limit, CPU_STK_SIZE len, OS_OPT opt)
{

        CPU_INT32U *stk;
        CPU_INT32U temp = (CPU_INT32U)(base + len -1);
        stk = (CPU_INT32U  *)temp;

        *(stk)    = (CPU_INT32U)p_task;       /* Entry Point                                        */
        *(--stk)  = (CPU_INT32U)0;             /* LR                                                 */

        *(--stk)  = (CPU_INT32U)0;             /* R12                                                */
        *(--stk)  = (CPU_INT32U)0;             /* R11                                                */
        *(--stk)  = (CPU_INT32U)0;             /* R10                                                */
        *(--stk)  = (CPU_INT32U)0;             /* R9                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R8                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R7 :                                               */
        *(--stk)  = (CPU_INT32U)0;             /* R6                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R5                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R4                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R3                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R2                                                 */
        *(--stk)  = (CPU_INT32U)0;             /* R1                                                 */
        *(--stk)  = (CPU_INT32U)p_arg;         /* R0 argument                                        */

        *(--stk)  = (CPU_INT32U)0x00000013L;   /* CPSR                                               */

        return stk;
}

CPU_INT08U  CPU_CntLeadZerosTbl[256] = {                             /* Data vals :                      */

/*   0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F   */
    8u,  7u,  6u,  6u,  5u,  5u,  5u,  5u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  4u,  /*   0x00 to 0x0F                   */
    3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  3u,  /*   0x10 to 0x1F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x20 to 0x2F                   */
    2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  2u,  /*   0x30 to 0x3F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x40 to 0x4F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x50 to 0x5F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x60 to 0x6F                   */
    1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  1u,  /*   0x70 to 0x7F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x80 to 0x8F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0x90 to 0x9F                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xA0 to 0xAF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xB0 to 0xBF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xC0 to 0xCF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xD0 to 0xDF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  /*   0xE0 to 0xEF                   */
    0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u,  0u   /*   0xF0 to 0xFF                   */
};


CPU_DATA  CPU_CntLeadZeros(CPU_DATA val)
{
	CPU_INT08U data;
	CPU_INT08U res;

	data = (val >> 24) & 0xFF;
	res = CPU_CntLeadZerosTbl[data];
	if(8 != res) {

		return res;
	}

	
	data = (val >> 16) & 0xFF;
	res = CPU_CntLeadZerosTbl[data];
	if(8 != res) {

		return (8 + res);
	}

	
	data = (val >> 8) & 0xFF;
	res = CPU_CntLeadZerosTbl[data];
	if(8 != res) {

		return  (16 + res);
	}

	data = val & 0xFF;
	res = CPU_CntLeadZerosTbl[data];

	return (24 + res);
}


void OSTaskCreateHook(OS_TCB* p_tcb )
{
	printk("task created here \n");
}

void OSTaskDelHook(OS_TCB* p_tcb)
{}

void OSIdleTaskHook()
{}

void OSStatTaskHook()
{}

void OSTimeTickHook()
{}

void OSTCBInitHook(OS_TCB* p_tcb)
{}

void OSInitHook()
{}

void OSTaskReturnHook(OS_TCB* p_tcb)
{}

void raise(int sig)
{}



