SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' 

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

echo "${GREEN}config.sh -> C flags ${NC}"

CFLAGS='-O2 -g -nostdlib -ffreestanding'

if [ -z "$NDEBUG" ]; then
	CFLAGS='-O2 -g -nostdlib -ffreestanding'
  echo "${RED}Debug Flags applied${NC}"
fi

echo "${GREEN}CFLAGS: ${CFLAGS}${NC}"

export CFLAGS
export CPPFLAGS=''

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
