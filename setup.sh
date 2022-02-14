/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -nodefaultlibs -m32 -g -c "./src/kernel.c" -o "kernel.o"
nasm "./src/kernel_entry.asm" -f elf -o "kernel_entry.o"
/usr/local/i386elfgcc/bin/i386-elf-ld -o "full_kernel.bin" -Ttext 0x1000 "kernel_entry.o" "kernel.o" --oformat binary
nasm "./src/boot.asm" -f bin -o "boot.bin"
cat "boot.bin" "full_kernel.bin" > "everything.bin"
nasm "./src/zeroes.asm" -f bin -o "zeroes.bin"
cat "everything.bin" "zeroes.bin" > "OS.bin"
DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0 qemu-system-x86_64 "OS.bin" -m 128M