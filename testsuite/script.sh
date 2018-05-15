#! /bin/bash
for f in *.sh ; do
	base=$(basename "$f" '.sh')
	sed -i "s/strace -ff -o ../script.strace cp/strace\ -ff\ -o ..\/$base.strace strace -ff -o ../script.strace cp/g" "$f"
done
