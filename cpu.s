
.global raw_int_switch
.global port_task_switch
.global OS_CPU_SR_Save
.global OS_CPU_SR_Restore
.global OSStartHighRdy


.equ SRCPND,    0x4a000000
.equ INTPND,    0x4a000010
.equ rEINTPEND, 0x560000a8
.equ INTOFFSET, 0x4a000014


#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0


OS_CPU_SR_Save:
        MRS     R0, CPSR                                @ Set IRQ and FIQ bits in CPSR to disable all interrupts
        ORR     R1, R0, #0xC0
        MSR     CPSR_c, R1
        MRS     R1, CPSR                                @Confirm that CPSR contains the proper interrupt disable flags
        AND     R1, R1, #0xC0
        CMP     R1, #0xC0
        BNE     OS_CPU_SR_Save                          @ Not properly disabled (try again)
        MOV     PC, LR                                  @ Disabled, return the original CPSR contents in R0


OS_CPU_SR_Restore:
        MSR     CPSR_c, R0
        MOV     PC, LR



OSStartHighRdy:
        MSR             CPSR_cxsf,#0x13|0xc0     @Switch to SVC mode with IRQ&FIQ disable

        @----------------------------------------------------------------------------------
        @               SP = raw_task_active->task_stack;
        @----------------------------------------------------------------------------------
        LDR     R0, =OSTCBCurPtr
        LDR     R0, [R0]
        LDR     SP, [R0]

        @----------------------------------------------------------------------------------
        @ Prepare to return to proper mode
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^


port_task_switch:
        STMFD   SP!, {LR}           @PC
        STMFD   SP!, {R0-R12, LR}   @R0-R12 LR
        MRS     R0,  CPSR       @Push CPSR
        STMFD   SP!, {R0}

        @----------------------------------------------------------------------------------
        @               raw_task_active->task_stack = SP
        @----------------------------------------------------------------------------------
        LDR             R0, =OSTCBCurPtr
        LDR             R0, [R0]
        STR             SP, [R0]

        @----------------------------------------------------------------------------------
        @ raw_task_active= high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSPrioHighRdy
        LDR             R1, =OSPrioCur
        LDRB            R0, [R0]
        STRB            R0, [R1]


        @----------------------------------------------------------------------------------
        @ raw_task_active= high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSTCBHighRdyPtr
        LDR             R1, =OSTCBCurPtr
        LDR             R0, [R0]
        STR             R0, [R1]


        @----------------------------------------------------------------------------------
        @  high_ready_obj->task_stack;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSTCBHighRdyPtr
        LDR             R0, [R0]
        LDR             SP, [R0]

        @----------------------------------------------------------------------------------
        @Restore New task context
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}               @POP CPSR
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^


raw_int_switch:

        @----------------------------------------------------------------------------------
        @ raw_task_active= high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSPrioHighRdy
        LDR             R1, =OSPrioCur
        LDRB            R0, [R0]
        STRB            R0, [R1]


        @----------------------------------------------------------------------------------
        @ raw_task_active= high_ready_obj;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSTCBHighRdyPtr
        LDR             R1, =OSTCBCurPtr
        LDR             R0, [R0]
        STR             R0, [R1]


        @----------------------------------------------------------------------------------
        @  high_ready_obj->task_stack;
        @----------------------------------------------------------------------------------
        LDR             R0, =OSTCBHighRdyPtr
        LDR             R0, [R0]
        LDR             SP, [R0]

        @----------------------------------------------------------------------------------
        @Restore New task context
        @----------------------------------------------------------------------------------
        LDMFD   SP!, {R0}               @POP CPSR
        MSR     SPSR_cxsf, R0
        LDMFD   SP!, {R0-R12, LR, PC}^



