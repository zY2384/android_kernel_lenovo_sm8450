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
    CMD_INIT_KEY = 0xA100,
    CMD_READ_MEM = 0xA200,
    CMD_WRITE_MEM = 0xA300,
    CMD_MODULE_BASE = 0xA400,
};