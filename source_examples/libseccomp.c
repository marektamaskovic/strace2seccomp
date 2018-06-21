int myapp_libseccomp_start(void)
{
	int rc;
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_KILL);

	if (ctx == NULL)
		return -ENOMEM;

	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);

	if (rc < 0)
		goto out;

	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);

	if (rc < 0)
		goto out;

	rc = seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 3,
		SCMP_A0(SCMP_CMP_EQ, STDIN_FILENO),
		SCMP_A1(SCMP_CMP_NE, 0x0),
		SCMP_A2(SCMP_CMP_LT, SSIZE_MAX)
	);

	if (rc < 0)
		goto out;

	rc = seccomp_load(ctx);

out:
	seccomp_release(ctx);
	return rc;
}
