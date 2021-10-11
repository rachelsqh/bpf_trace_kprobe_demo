srctree = /usr/src/linux-source-5.10
objtree = srctree
all:
	$(Q)clang -O2 -D__KERNEL__ -target bpf -I/usr/include/x86_64-linux-gnu/ -c trace_kprobe_kern.c -o trace_kprobe_kern.o
	$(Q)gcc -o loader loader.c bpf_load.c $(srctree)/tools/lib/bpf/libbpf.a /usr/lib/x86_64-linux-gnu/libz.a /usr/lib/x86_64-linux-gnu/libelf.a
clean:
	rm -rf *.o loader
