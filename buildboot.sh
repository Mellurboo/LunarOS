#!/bin/sh
set -e
. ./build.sh

mkdir -p LUNAR
mkdir -p LUNAR/boot
mkdir -p LUNAR/boot/grub

cp sysroot/boot/lunaros.kernel LUNAR/boot/lunaros.kernel
cat > LUNAR/boot/grub/grub.cfg << EOF
menuentry "lunaros" {
	multiboot /boot/lunaros.kernel
}
EOF
grub-mkrescue -o lunaros.iso LUNAR
