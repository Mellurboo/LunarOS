#!/bin/sh
set -e
. ./buildboot.sh

QEMU_BIN="qemu-system-$(./target-triplet-to-arch.sh $HOST)"
ISO_FILE="lunaros.iso"

$QEMU_BIN -cdrom $ISO_FILE
