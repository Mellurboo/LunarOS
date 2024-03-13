#!/bin/sh
set -e
. ./buildboot.sh

QEMU_BIN="qemu-system-$(./target-triplet-to-arch.sh $HOST)"
ISO_FILE="lunaros.iso"

if [ "$1" = "vb" ]; then
    # Run QEMU in debug mode with all debugging options enabled and redirect output to log file
    LOG_FILE="qemu_debug.log"
    $QEMU_BIN -cdrom $ISO_FILE -m 256 -d cpu_reset,guest_errors,int > $LOG_FILE 2>&1
else
    # Run QEMU normally
    $QEMU_BIN -cdrom $ISO_FILE -m 256
fi
