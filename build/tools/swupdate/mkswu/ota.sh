#!/bin/sh

echo "ota"

function preinst() {
    echo "preinst"
}

function postinst() {
    echo "postinst"
    result=$(devmem 0x2390024)
    slota=$(( (result >> 2) & 1 ))
    # If system A is being started, switch to system B after the upgrade.
    if [ $slota -eq 1 ]; then
        /etc/init.d/S99checkboot systemB
    else
        /etc/init.d/S99checkboot systemA
    fi
}

if [ "$1" == "preinst" ]; then
    preinst
fi

if [ "$1" == "postinst" ]; then
    postinst
fi
