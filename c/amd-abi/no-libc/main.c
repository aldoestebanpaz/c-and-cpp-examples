#include <sys/syscall.h>

long _syscall(unsigned long syscallnum, void *a0, void *a1, void *a2, void *a3, void *a4, void *a5);

unsigned long strlen(const char *str)
{
    int count = 0;
    while(*str++) {
        count++;
    }
    return count;
}

void sys_print_string(char *str)
{
    _syscall(SYS_write, /*stdout*/ (void *)1, (void *)str, (void *)strlen(str), 0, 0, 0);
}

void sys_exit(unsigned long errorcode)
{
    _syscall(SYS_exit, /*stdout*/ (void *)errorcode, 0, 0, 0, 0, 0);
}

void main()
{
    // You may want `asm volatile` if you use this in more than one place, otherwise the compiler can assume that the asm statement always produces the same output (because the input is always the same: the empty set of inputs.)
    register volatile const unsigned long reg_rsp asm("rsp");
    // printf("RSP: %lx", reg_rsp);

    char* msg = "Hello World";
    char* msg2 = "Hello World2";

    sys_print_string(msg);
    sys_print_string(msg2);
    sys_exit(0);

    // no include epiloge
    __builtin_unreachable();
}
