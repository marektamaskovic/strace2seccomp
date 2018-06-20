/*
 * Generated seccomp template with initialized filter using st2se.
 * link with -lseccomp
 */

#ifdef __cplusplus
    #define NULL nullptr
    #include <cstdio>
#else
    #include <stdio.h>
#endif

#include <seccomp.h>

int setup_seccomp_whitelist(){

    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
    
    int ret = 0;


    // seccomp rules 
    //-------------------------------------------------------------------------
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access), 0,
        SCMP_A1(SCMP_CMP_EQ, R_OK)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 0,
        SCMP_A0(SCMP_CMP_EQ, ARCH_SET_FS)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(chdir), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0,
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, 5),
        SCMP_A0(SCMP_CMP_GE, 4), SCMP_A0(SCMP_CMP_LE, 7)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0,
        SCMP_A0(SCMP_CMP_EQ, 0)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fcntl), 0,
        SCMP_A0(SCMP_CMP_EQ, 7),
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, 6),
        SCMP_A1(SCMP_CMP_EQ, F_GETFL),
        SCMP_A1(SCMP_CMP_GE, F_GETFD), SCMP_A1(SCMP_CMP_LE, F_SETFL)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0,
        SCMP_A0(SCMP_CMP_EQ, 5),
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, 6)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(futex), 0,
        SCMP_A1(SCMP_CMP_EQ, FUTEX_WAKE_PRIVATE),
        SCMP_A2(SCMP_CMP_EQ, 2147483647)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getcwd), 0,
        SCMP_A1(SCMP_CMP_EQ, 4096)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(getdents), 0,
        SCMP_A0(SCMP_CMP_GE, 4), SCMP_A0(SCMP_CMP_LE, 6),
        SCMP_A1(SCMP_CMP_GE, 4), SCMP_A1(SCMP_CMP_LE, 6),
        SCMP_A2(SCMP_CMP_EQ, 32768)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(ioctl), 0,
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, 2),
        SCMP_A1(SCMP_CMP_EQ, TCGETS)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0,
        SCMP_A1(SCMP_CMP_GE, 8192), SCMP_A1(SCMP_CMP_LE, 3914128),
        SCMP_A1(SCMP_CMP_EQ, 12288),
        SCMP_A4(SCMP_CMP_GE, -1), SCMP_A4(SCMP_CMP_LE, 4)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 0,
        SCMP_A1(SCMP_CMP_GE, 4096), SCMP_A1(SCMP_CMP_LE, 2097152),
        SCMP_A1(SCMP_CMP_EQ, 2093056),
        SCMP_A2(SCMP_CMP_GE, PROT_NONE), SCMP_A2(SCMP_CMP_LE, PROT_READ)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0,
        SCMP_A1(SCMP_CMP_EQ, 135168),
        SCMP_A1(SCMP_CMP_GE, 220291), SCMP_A1(SCMP_CMP_LE, 266240)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 0,
        SCMP_A0(SCMP_CMP_EQ, AT_FDCWD)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(pipe), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(prlimit64), 0,
        SCMP_A0(SCMP_CMP_EQ, 0),
        SCMP_A1(SCMP_CMP_EQ, RLIMIT_STACK)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0,
        SCMP_A0(SCMP_CMP_EQ, 5),
        SCMP_A0(SCMP_CMP_GE, 4), SCMP_A0(SCMP_CMP_LE, 6),
        SCMP_A2(SCMP_CMP_GE, 1), SCMP_A2(SCMP_CMP_LE, 4096),
        SCMP_A2(SCMP_CMP_GE, 195), SCMP_A2(SCMP_CMP_LE, 198)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(readlink), 0,
        SCMP_A2(SCMP_CMP_EQ, 4095)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigaction), 0,
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, ),
        SCMP_A3(SCMP_CMP_EQ, 8)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigprocmask), 0,
        SCMP_A0(SCMP_CMP_EQ, SIG_SETMASK),
        SCMP_A0(SCMP_CMP_GE, SIG_BLOCK), SCMP_A0(SCMP_CMP_LE, SIG_UNBLOCK),
        SCMP_A3(SCMP_CMP_EQ, 8)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_robust_list), 0,
        SCMP_A1(SCMP_CMP_EQ, 24)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(set_tid_address), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(stat), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(sysinfo), 0);
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(vfork), 0,
        SCMP_A0(SCMP_CMP_EQ, )
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(wait4), 0,
        SCMP_A0(SCMP_CMP_EQ, -1),
        SCMP_A2(SCMP_CMP_EQ, 0)
    );
    ret |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0,
        SCMP_A0(SCMP_CMP_GE, 1), SCMP_A0(SCMP_CMP_LE, 5),
        SCMP_A2(SCMP_CMP_GE, 1), SCMP_A2(SCMP_CMP_LE, 22)
    );
    //-------------------------------------------------------------------------

    if (seccomp_load(ctx) != 0) {
        ret = 2;
        goto out;
    }

    return ret;

out:
    seccomp_release(ctx);
    return ret;
}

int main()
{
    setup_seccomp_whitelist();

    // Put your code below
    return 0;

}
