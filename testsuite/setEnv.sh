#! /bin/bash

#===============================================================================
# Information
#===============================================================================
# Author: Marek Tamaskovic



#===============================================================================
# Global Variables
#===============================================================================

Color_Off='\033[0m'       # Text Reset
BWhite='\033[1;37m'       # White
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green

coreutils='coreutils-8.29'
findutils='findutils-4.6.0'
usbguard='usbguard-0.7.2'
testovac='testovac'

nproc=8

#===============================================================================
# Functions
#===============================================================================


printHelp(){
	echo -e "Usage:"
	echo -e "\tAvailable commands: prep applyPolicy make"
	echo -e ""
	echo -e "\thelp\t\t- print this help"
	echo -e "\tprep\t\t- download, extract, configure packages"
	echo -e "\tapplyPolicy\t- generate strace, generate policy, patch sources"
	echo -e "\tmake\t\t- make"
	echo -e "\ttests\t\t- run tests"
	echo -e "\tclean\t\t- reset testsfolder"
	echo -e "\trevertPatches\t- revert previously applied patches"
	echo -e "\tstraceON\t- turn on strace logging"
	echo -e "\tstraceOFF\t- revert strace logging"
}

download(){
    echo -e "$BWhite" "Dowloading findutils ..." "$Color_Off"
    wget -nv https://ftp.gnu.org/pub/gnu/findutils/findutils-4.6.0.tar.gz

    echo -e "$BWhite" "Dowloading coreutils ..." "$Color_Off"
    wget -nv https://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz

    echo -e "$BWhite" "Dowloading usbguard ..." "$Color_Off"
    wget -nv https://github.com/USBGuard/usbguard/releases/download/usbguard-0.7.2/usbguard-0.7.2.tar.gz

    echo -e "$BWhite" "Dowloading testovac ..." "$Color_Off"
    wget -nv https://github.com/tammar96/ISA-testovac/releases/download/untagged-7d8ed3a74b854254df64/testovac.tar
}

extract(){
    echo -e "$BWhite" "Extracting sources ..." "$Color_Off"
    tar -xzf findutils-4.6.0.tar.gz
    tar -xJf coreutils-8.29.tar.xz
    tar -xzf usbguard-0.7.2.tar.gz
    mkdir -p testovac && tar -xf testovac.tar -C testovac
}

configure(){
    echo -e "$BWhite" "Configuring" "$BGreen" "$1" "$Color_Off"
    cd $1 && shift && ./configure $* && cd ..
}

runMake(){
    echo -e "$BWhite" "Making" "$BGreen" "$1" "$Color_Off"
    cd $1 && make -j 16 && cd ..
}

__run_tests() {
	# start coreutils tests for specific component
      #strace -s 0 -ff -o "coreutils.strace" \
    /usr/bin/time -o coreutils.time -a -- \
      make -j$(nproc) check TESTS="$*" SUBDIRS=. VERBOSE=yes \
      RUN_VERY_EXPENSIVE_TESTS=yes RUN_EXPENSIVE_TESTS=yes
}

run_coreutils_tests() {
	echo -e "\t$BWhite" "COREUTILS:" "$Color_Off"
	cd `echo $coreutils`
	__run_tests tests/cp/*.sh
	mv coreutils.strace* ../
	# __run_tests tests/rm/*.sh
	# mv coreutils.strace ../rm.strace
	cd ..
}

applyStracePatch() {
	cd `echo $coreutils`
	git init
	git add -A
	git commit -m "init"
	git apply ../cp.tests.2.patch
	git add -u
	git commit -m "applied strace patch"
	cd ..
}

revertStracePatch() {
	cd `echo $coreutils`
	git reset --hard HEAD~1
	cd ..
}

#===============================================================================
# MAIN
#===============================================================================

main(){

	echo -e "$BWhite" "Start 'set environment' script ..." "$Color_Off"

	if [ "$1" = "help" ]; then
		# Print help
		printHelp

	elif [ "$1" = "prep" ]; then
	    #Prepare

	    if [ "$#" -eq 2 ]; then
	    	if [ "$2" != "--local" ]; then
	    		download
	    	else
	    		if [ ! -e "`echo $findutils`.tar.gz" ]; then
	    			echo "Provide" "`echo $findutils`.tar.gz"
	    			exit 1
	    		fi

	    		if [ ! -e "`echo $coreutils`.tar.xz" ]; then
	    			echo "Provide" "`echo $coreutils`.tar.xz"
	    			exit 1
	    		fi

	    		if [ ! -e "`echo $usbguard`.tar.gz" ]; then
	    			echo "Provide" "`echo $usbguard`.tar.gz"
	    			exit 1
	    		fi

	    		if [ ! -e "`echo $testovac`.tar" ]; then
	    			echo "Provide" "`echo $testovac`.tar.gz"
	    			exit 1
	    		fi
	    	fi
	    else
	    	download
	    fi

	    extract

	    echo -e "$BWhite" "Patch Makefile.in files" "$Color_Off"
	    patch `echo $findutils`/find/Makefile.in find.Makefile.in.patch
	    patch `echo $coreutils`/Makefile.in coreutils.Makefile.in.patch

	    # Configure sources
	    configure $coreutils &
	    configure $findutils &
	    configure $usbguard --with-crypto-library=gcrypt --with-bundled-pegtl --with-bundled-catch &
	    # testovac doesn't provide a configure script

	    wait

	elif [ "$1" = "applyPolicy" ]; then
	    # Generate policies
	    echo -e "$BRed" "TODO:$Color_Off run ./st2se"

	    # Modify patch files
	    echo -e "$BRed" "TODO:$Color_Off modify patches"

	    # Patch
	    echo -e "$BWhite" "Patch sources" "$Color_Off"
	    patch `echo $findutils`/find/ftsfind.c find.ftsfind.c.patch

	    patch `echo $coreutils`/src/cp.c coreutils.cp.c.patch
	    patch `echo $coreutils`/src/rm.c coreutils.src_rm.c.patch

	elif [ "$1" = "revertPatches" ]; then

	    echo -e "$BWhite" "Revert previously applied patches" "$Color_Off"

	    patch --reverse `echo $findutils`/find/ftsfind.c find.ftsfind.c.patch

	    patch --reverse `echo $coreutils`/src/cp.c coreutils.cp.c.patch
	    patch --reverse `echo $coreutils`/src/rm.c coreutils.src_rm.c.patch

	elif [ "$1" = "straceON" ]; then

            applyStracePatch

	elif [ "$1" = "straceOFF" ]; then

	    revertStracePatch

	elif [ "$1" = "make" ]; then
	    # Make custom binaries
	     runMake $coreutils &
	    # runMake $findutils &
	    # runMake $usbguard &
	    # runMake $testovac &

	    wait

	elif [ "$1" = "tests" ]; then
		#Run tests
		echo -e "$BWhite" "Running tests" "$Color_Off"
		run_coreutils_tests

	elif [ "$1" = "clean" ]; then
	    # Remove packages
	    rm -rf ./`echo $findutils`/
	    rm -rf ./`echo $findutils`.tar.gz
	    rm -rf ./`echo $coreutils`/
	    rm -rf ./`echo $coreutils`.tar.xz
	    rm -rf ./`echo $usbguard`/
	    rm -rf ./`echo $usbguard`.tar.gz
	    rm -rf ./`echo $testovac`/
	    rm -rf ./`echo $testovac`.tar

	else
		printHelp
	fi

	echo -e "$BWhite" "End 'set environment' script ..." "$Color_Off"

}

#===============================================================================
# Run Main Function
#===============================================================================
main $*

