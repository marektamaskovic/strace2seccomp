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
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(access),
        SCMP_A0(SCMP_CMP_EQ, 0),
        SCMP_A1(SCMP_CMP_GE, 0), SCMP_A1(SCMP_CMP_LE, R_OK)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(arch_prctl),
        SCMP_A0(SCMP_CMP_GE, 0), SCMP_A0(SCMP_CMP_LE, ARCH_SET_FS)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve),
        SCMP_A0(SCMP_CMP_EQ, 0),
        SCMP_A1(SCMP_CMP_EQ, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group),
        SCMP_A0(SCMP_CMP_GE, 0), SCMP_A0(SCMP_CMP_LE, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap),
        SCMP_A1(SCMP_CMP_GE, 0), SCMP_A1(SCMP_CMP_LE, 14576),
        SCMP_A2(SCMP_CMP_GE, 0), SCMP_A2(SCMP_CMP_LE, PROT_READ|PROT_WRITE),
        SCMP_A3(SCMP_CMP_GE, 0), SCMP_A3(SCMP_CMP_LE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS),
        SCMP_A4(SCMP_CMP_GE, -1), SCMP_A4(SCMP_CMP_LE, 0),
        SCMP_A5(SCMP_CMP_GE, 0), SCMP_A5(SCMP_CMP_LE, 0)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mprotect),
        SCMP_A1(SCMP_CMP_GE, 0), SCMP_A1(SCMP_CMP_LE, 2093056),
        SCMP_A1(SCMP_CMP_GE, 4096), SCMP_A1(SCMP_CMP_LE, 16384),
        SCMP_A2(SCMP_CMP_GE, 0), SCMP_A2(SCMP_CMP_LE, PROT_READ)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap),
        SCMP_A1(SCMP_CMP_GE, 0), SCMP_A1(SCMP_CMP_LE, 213488)
    );
    rc |= seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat),
        SCMP_A0(SCMP_CMP_GE, 0), SCMP_A0(SCMP_CMP_LE, AT_FDCWD),
        SCMP_A1(SCMP_CMP_EQ, 0),
        SCMP_A2(SCMP_CMP_GE, 0), SCMP_A2(SCMP_CMP_LE, O_RDONLY|O_CLOEXEC)
    );
    //-------------------------------------------------------------------------

    if (seccomp_load(ctx) != 0) {
        rc = 2;
        goto out;
    }
    return rc;
out:
    seccomp_release(ctx);
    return rc;
}

int main()
{
    // setup_seccomp_whitelist(&ctx);
    setup_seccomp_whitelist();
    // Put your code below
    return 0;
}
