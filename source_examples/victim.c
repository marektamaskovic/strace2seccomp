if (access("file", W_OK) != 0) {
	exit(1);
}

fd = open("file", O_WRONLY);
write(fd, buffer, sizeof(buffer));