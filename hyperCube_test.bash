#!/bin/bash

set -e

cd /home/lance/git/x3domVR_tutorial

function catch()
{
    killall firefox
    exit
}


rm -rf profiles/

mkdir profiles

screens="0 2 4 6 8 10 12 14"

set -x

for i in $screens ; do
    ./mk_firefoxProfile.bash 0.$i ${PWD}/profiles/0.$i
done

trap catch SIGINT SIGSTOP SIGQUIT SIGTERM

for i in $screens ; do
    DISPLAY=:0.$i firefox -P 0.$i ./065_x_fullscreen/run.html &
    #DISPLAY=:0.$i firefox -P 0.$i ./069_xx_fullscreen/run.html &
    sleep 6
done

for i in $screens ; do
    DISPLAY=:0.$i ./clickWindow
    sleep 2
done

while true ; do
    sleep 10
done


