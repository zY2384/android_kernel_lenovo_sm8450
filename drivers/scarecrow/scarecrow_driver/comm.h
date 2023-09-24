typedef struct _COPY_MEMORY
{
    pid_t pid;
    uintptr_t addr;
    void* buffer;
    size_t size;
} COPY_MEMORY, *PCOPY_MEMORY;

typedef struct _MODULE_BASE
{
    pid_t pid;
    char* name;
    uintptr_t base;
} MODULE_BASE, *PMODULE_BASE;

enum CMD
{
    CMD_INIT_KEY = 0x1000,
    CMD_READ_MEM = 0x2000,
    CMD_WRITE_MEM = 0x3000,
    CMD_MODULE_BASE = 0x4000,
};