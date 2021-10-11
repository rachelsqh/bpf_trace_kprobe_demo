
//typedef struct {
//	s64 counter;
//} atomic64_t;
//#include <uapi/linux/posix_types.h>
//#include <uapi/asm-generic/posix_types.h>
//#include <linux/bpf.h>

#include <bpf/bpf_tracing.h>
#include "vmlinux.h"
#include <bpf/bpf_helpers.h>
#ifndef SEC
#define SEC(NAME) __attribute__((section(NAME),used))
#endif
SEC("tracepoint/syscalls/sys_enter_execve")
 int bpf_prog(void *ctx)
{
	char msg[] = "hello,bpf world";

	bpf_trace_printk(msg,sizeof(msg));
	return 0;
}

#define _(P)                                                                   \
	({                                                                     \
		typeof(P) val = 0;                                             \
		bpf_probe_read_kernel(&val, sizeof(val), &(P));                \
		val;                                                           \
	})

SEC("kprobe/begin_new_exec")
int prog(struct pt_regs *ctx)
{

	char file_name[] = "comm = %s\n";
	char buf_comm[16];
	bpf_get_current_comm(buf_comm,sizeof(buf_comm));

	
	bpf_trace_printk(file_name,sizeof(file_name),buf_comm);
	return 0;
}

char _license[] SEC("license") = "GPL";
