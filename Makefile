

CC=arm-linux-gcc
LD=arm-linux-ld
OBJCOPY=arm-linux-objcopy

CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Trtos.lds -Ttext 30000000  

OBJS=   init.o start.o boot.o abnormal.o cpu.o mmu.o print.o interrupt.o  \
	os_app_hooks.o os_cfg_app.o os_core.o os_dbg.o os_flag.o os_int.o os_mem.o os_msg.o\
	os_mutex.o os_pend_multi.o os_prio.o os_q.o os_sem.o os_stat.o os_task.o os_tick.o os_time.o os_tmr.o os_var.o\
	test_task.o test_sem.o test_mutex.o port.o
 
.c.o:
	$(CC) $(CFLAGS) -c -I. $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

rtos:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc 
	$(OBJCOPY) -O binary $@ rtos.bin

clean:
	rm *.o rtos rtos.bin rtos.txt -f
