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

int main(int argc, char *argv[])
{
    int rc = -1;
    scmp_filter_ctx ctx;

    ctx = seccomp_init(SCMP_ACT_KILL);
    
    if (ctx == NULL) {
        goto out;
    }
    else {
        rc = 0;
    }

    // seccomp rules 
    //-------------------------------------------------------------------------
    __insert_tag

    //-------------------------------------------------------------------------

    // Put your code below

out:
    seccomp_release(ctx);
    return -rc;
}