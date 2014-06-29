
#include "os.h"

extern int test_switch;

static OS_TCB tcb1;
static OS_TCB tcb2;

static CPU_STK stk1[1024];
static CPU_STK stk2[1024];

static void test_task1(void* p_arg){

	OS_ERR err;
	
	p_arg = p_arg;

	while(1) {

		printk("hi ");
		OSTimeDly(150, OS_OPT_TIME_DLY, &err);
	}
}

static void test_task2(void* p_arg){

	OS_ERR err;
	
	p_arg = p_arg;

	while(1) {

		printk("go ");
		OSTimeDly(7, OS_OPT_TIME_DLY, &err);
	}
}

void test_task()
{
	OS_ERR err;

	if(1 == test_switch) {

		return;
	}

	test_switch = 1;

	OSTaskCreate(&tcb1, 
			"task1", 
			test_task1, 
			0, 
			7, 
			&stk1[0], 
			256, 
			1024, 
			0, 
			0, 
			0,
			OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
			&err );

	OSTaskCreate(&tcb2, 
			"task2", 
			test_task2, 
			0, 
			5, 
			&stk2[0], 
			256, 
			1024, 
			0, 
			0, 
			0,
			OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
			&err );

}



