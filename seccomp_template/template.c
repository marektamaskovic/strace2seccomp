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

int setup_seccomp_whitelist(scmp_filter_ctx *ctx){

    if(ctx == NULL){
        fprintf(stderr, "%s %s %s\n", "Error:", __func__, ": ctx is NULL\n");
        return -1;
    }

    int rc = 0;

    // seccomp rules 
    //-------------------------------------------------------------------------
    //-------------------------------------------------------------------------

    return rc;
}

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

    setup_seccomp_whitelist(&ctx);

    // Put your code below

out:
    seccomp_release(ctx);
    return -rc;
}