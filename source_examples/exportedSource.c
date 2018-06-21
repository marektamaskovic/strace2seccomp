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
    int rc = 0;

    // seccomp rules
    //-------------------------------------------------------------------------
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access), 2,
        SCMP_A0(SCMP_CMP_EQ, 0),
        SCMP_A1(SCMP_CMP_IN_RANGE, 0, R_OK)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl), 1,
        SCMP_A0(SCMP_CMP_IN_RANGE, 0, ARCH_SET_FS)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 2,
        SCMP_A0(SCMP_CMP_EQ, 0),
        SCMP_A1(SCMP_CMP_EQ, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 1,
        SCMP_A0(SCMP_CMP_GE, 0), SCMP_A0(SCMP_CMP_LE, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 5,
        SCMP_A1(SCMP_CMP_IN_RANGE, 0, 14576),
        SCMP_A2(SCMP_CMP_IN_RANGE, 0, PROT_READ|PROT_WRITE),
        SCMP_A3(SCMP_CMP_IN_RANGE, 0, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS),
        SCMP_A4(SCMP_CMP_IN_RANGE, -1, 0),
        SCMP_A5(SCMP_CMP_IN_RANGE, 0, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 2
        SCMP_A1(SCMP_CMP_IN_RANGE, 0, 4096),
        SCMP_A2(SCMP_CMP_IN_RANGE, 0, PROT_READ)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect), 2
        SCMP_A1(SCMP_CMP_IN_RANGE, 16384, 2093056),
        SCMP_A2(SCMP_CMP_IN_RANGE, 0, PROT_READ)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 1
        SCMP_A1(SCMP_CMP_IN_RANGE, 0, 213488)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 3
        SCMP_A0(SCMP_CMP_IN_RANGE, 0, AT_FDCWD),
        SCMP_A1(SCMP_CMP_EQ, 0),
        SCMP_A2(SCMP_CMP_IN_RANGE, 0, O_RDONLY|O_CLOEXEC)
    );
    //-------------------------------------------------------------------------

    if (rc != 0) {
        goto out;
    }

    if (seccomp_load(ctx) != 0) {
        rc = 2, goto out;
    }
    return rc;
out:
    seccomp_release(ctx);
    return rc;
}

int main()
{
    // setup and load seccomp whitelist
    if (setup_seccomp_whitelist() != 0) {
        return 1;
    }
    // Put your code below
    return 0;
}
