#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/somendraOS.kernel isodir/boot/somendraOS.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "somendraOS" {
	multiboot /boot/somendraOS.kernel
}
EOF
grub-mkrescue -o somendraOS.iso isodir
