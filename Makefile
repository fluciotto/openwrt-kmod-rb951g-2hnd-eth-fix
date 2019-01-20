OPENWRT=${HOME}/Development/openwrt

KERNEL=${OPENWRT}/build_dir/target-mips_24kc_musl/linux-ar71xx_mikrotik/linux-4.9.120
TOOLCHAIN=${OPENWRT}/staging_dir/toolchain-mips_24kc_gcc-7.3.0_musl
CC=${TOOLCHAIN}/bin/mips-openwrt-linux-gcc
LD=${TOOLCHAIN}/bin/mips-openwrt-linux-ld

obj-m += rb951g-2hnd-eth-fix.o

all:
	make -C ${KERNEL} ARCH="mips" CC="$(CC)" M=$(PWD) modules

clean:
	make -C ${KERNEL} CC="$(CC)" M=$(PWD) clean
