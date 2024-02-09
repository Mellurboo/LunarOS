#					quick note also the stack might be fucked
#	REFERENCE SHIT BECAUSE IM REALLY BAD AT MEMORISING THINGS
#		VGA PT (0x0...) 0 -> (0xC03FFFFF) 768
#			for the VGA Memory there are 768 entires
#			we do map bot the start and the (end * 4)
#


# Multiboot 
.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# reserve stack space (16kb)
.section .bootstrap_stack, "aw", @nobits
.align 16
btm_stack:
.skip 16384
top_stack:

.section .bss, "aw", @nobits
	.align 4096
boot_page_dir:
	.skip 4096
boot_page_table:
	.skip 4096

# kernel entry
.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:
	# Boot page table, mapping the first and last addr (1023) and saving 1024 for the VGA Buffer
	# these are each 4bytes so we end up with a (1024 * 4)kb PAGE directory and table.
	movl $(boot_page_table - 0xC0000000), %edi
	movl $0, %esi				#first
	movl $1023, %ecx			#last + 1 reserve

	movl $top_stack, %esp
	xor %ebp, %ebp
	push %ebp


1:
	#Map the kernel
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl 4 + (_kernel_end - 0xC0000000), %esi
	jge 3f

	# map physicall addresses
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	#Page sizing (4096 bytes) this is including the size of all the entires in the boot table (each is 4bytes)
	addl $4096, %esi
	addl $4, %edi
	loop 1b

3:
	movl $(0x000B8000 | 0x003), boot_page_table - 0xC0000000 + 1023 * 4
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_dir - 0xC0000000 + 0
	movl $(boot_page_table - 0xC0000000 + 0x003), boot_page_dir - 0xC0000000 + 768 * 4
	movl $(boot_page_dir - 0xC0000000), %ecx
	movl %ecx, %cr3

	# the fun part (paging is enabled)
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0 

	lea 4f, %ecx 
	jmp *%ecx

.section .text
4:
	# we did it, anyway lets unmap all the defualt boring shit (identity mapping)
	movl $0, boot_page_dir + 0
	
	# this looks really dumb but we have to trigger the Translation lookaside buffer to reload
	movl %cr3, %ecx
	movl %ecx, %cr3

	mov $top_stack, %esp
	call kernel_main  

	cli
1:	hlt
	jmp 1b