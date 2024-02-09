#!/bin/sh
set -e
. ./buildboot.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom lunaros.iso
