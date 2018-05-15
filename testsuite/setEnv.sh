#! /bin/bash

Color_Off='\033[0m'       # Text Reset
BWhite='\033[1;37m'       # White
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green

coreutils='coreutils-8.29'
findutils='findutils-4.6.0'

download(){
    echo -e "$BWhite Dowloading findutils ... $Color_Off"
    wget -nv https://ftp.gnu.org/pub/gnu/findutils/findutils-4.6.0.tar.gz

    echo -e "$BWhite Dowloading coreutils ... $Color_Off"
    wget -nv https://ftp.gnu.org/gnu/coreutils/coreutils-8.29.tar.xz
}

extract(){
    echo -e "$BWhite Extracting sources ... $Color_Off"
    tar -xJf coreutils-8.29.tar.xz
    tar -xzf findutils-4.6.0.tar.gz
}

configure(){
    echo -e "$BWhite Configuring $BGreen $1 $Color_Off"
    cd $1 && ./configure && cd ..
}

runMake(){
    echo -e "$BWhite Making $BGreen $1 $Color_Off"
    cd $1 && make -j 8 && cd ..
}

echo -e "$BWhite Start preparing script ... $Color_Off"

if [ "$1" = "prep" ]; then
    #Prepare
    download
    extract
    # Configure sources
    configure $coreutils
    configure $findutils
fi

if [ "$1" = "applyPolicy" ]; then
    # Generate policies
    echo -e "$BRed TODO:$Color_Off run ./st2se"
    # Patch
    echo -e "$BRed TODO:$Color_Off patch sources"

fi

if [ "$1" = "make" ]; then
    # Make custom binaries
    runMake $coreutils
    runMake $findutils
fi

echo -e "$BWhite End preparing script ... $Color_Off"
