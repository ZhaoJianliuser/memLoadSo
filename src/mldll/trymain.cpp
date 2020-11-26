#include "memload/memload.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <dlfcn.h>

#if defined (__cplusplus) || defined (c_plusplus)
extern "C" {
#endif

#if defined(_DEBUG)
    #if defined(__linux__) || defined(__linux)
        #define CSDLL_LIBRARY_NAME          "csdll_debug"
        #define CSDLL_LIBRARY_FULLNAME      "libcsdll_debug.so"
    #else
        #error "Platform not supported"
    #endif
#else
    #if defined(__linux__) || defined(__linux)
        #define CSDLL_LIBRARY_NAME          "csdll"
        #define CSDLL_LIBRARY_FULLNAME      "libcsdll.so"
    #else
        #error "Platform not supported"
    #endif
#endif

#define CSDLL_LIBRARY_ADDSUM    "addsum"

typedef int (*fnAddsumProc)(int, int);

void PrintCWD(void)
{
    char pathname[1024] = {'\0'};

    if (readlink("/proc/self/exe", pathname, 1024) <=0) {
        fprintf(stderr, "[-] Get exepath failed\n");
    }
    fprintf(stdout, "[+] Current exepath: %s\n", pathname);

    if (getcwd(pathname, 1024) == NULL) {
        fprintf(stderr, "[-] Get current workdir failed\n");
    }
    fprintf(stdout, "[+] Current workdir: %s\n", pathname);
}

int LoadFromFile(void)
{
    void *handle = NULL;
    fnAddsumProc fnAddsum = NULL;
    int iret = 0;
    char curdir[512] = {'\0'};
    char pathname[1024] = {'\0'};

    PrintCWD();
    fprintf(stdout, "%s\n", "LoadFromFile ......");
    if (getcwd(curdir, 512) == NULL) {
        fprintf(stderr, "[-] Get current workdir failed\n");
        iret = 1;
        goto exit;
    }
    snprintf(pathname, 1024, "%s/%s", curdir, CSDLL_LIBRARY_FULLNAME);

    handle = dlopen(pathname, RTLD_NOW | RTLD_GLOBAL);
    if (handle == NULL)
    {
        fprintf(stderr, "Can't load library from file: %s\n", dlerror());
        iret = 2;
        goto exit;
    }

    fnAddsum = (fnAddsumProc)dlsym(handle, CSDLL_LIBRARY_ADDSUM);
    if (fnAddsum == NULL)
    {
        fprintf(stderr, "Can't get proc address: %s\n", dlerror());
        iret = 3;
        goto exit;
    }
    fprintf(stdout, "get proc address: %s - 0x%p\n", CSDLL_LIBRARY_ADDSUM, fnAddsum);
    fprintf(stdout, "From file proc result: %d\n", fnAddsum(1, 2));

    dlclose(handle);
    handle = NULL;
    iret = 0;

exit:
    if (handle != NULL)
    {
        dlclose(handle);
        handle = NULL;
    }

    return iret;
}

void* ReadLibrary(size_t* pSize)
{
    size_t read;
    void* result;
    FILE* fp;

    fp = fopen(CSDLL_LIBRARY_FULLNAME, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open so file: %s\n", CSDLL_LIBRARY_FULLNAME);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    *pSize = static_cast<size_t>(ftell(fp));
    if (*pSize == 0)
    {
        fclose(fp);
        return NULL;
    }

    result = (unsigned char *)malloc(*pSize);
    if (result == NULL)
    {
        fclose(fp);
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);
    read = fread(result, 1, *pSize, fp);
    fclose(fp);
    if (read != *pSize)
    {
        free(result);
        return NULL;
    }

    return result;
}

int LoadFromMemory(void)
{
    void *data = NULL;
    void *handle = NULL;
    fnAddsumProc fnAddsum = NULL;
    size_t size = 0;
    int iret = 0;

    PrintCWD();
    fprintf(stdout, "%s\n", "LoadFromMemory ......");

    data = ReadLibrary(&size);
    if (data == NULL)
    {
        iret = 1;
        goto exit;
    }

    handle = memory_load_library(data, size);
    if (handle == NULL)
    {
        fprintf(stderr, "Can't load library from memory: %s\n", memory_get_errormsg());
        iret = 2;
        goto exit;
    }

    fnAddsum = (fnAddsumProc)memory_get_procaddr(handle, CSDLL_LIBRARY_ADDSUM);
    if (fnAddsum == NULL)
    {
        printf("Can't get proc address: %s\n", memory_get_errormsg());
        iret = 3;
        goto exit;
    }
    fprintf(stdout, "get proc address: %s - 0x%p\n", CSDLL_LIBRARY_ADDSUM, fnAddsum);
    fprintf(stdout, "From memory proc result: %d\n", fnAddsum(1, 2));

    memory_free_library(handle);
    handle = NULL;
    iret = 0;

exit:
    if (handle != NULL)
    {
        memory_free_library(handle);
        handle = NULL;
    }

    if (data != NULL)
    {
        free(data);
        data = NULL;
    }

    return iret;
}

#if defined (__cplusplus) || defined (c_plusplus)
} /* End of extern "C" */
#endif

////======================

#ifdef MLDLL_TRYMAIN
#define _TRY_MAIN main
#else
#define _TRY_MAIN _try_main
#endif

int _TRY_MAIN(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
    fprintf(stdout, "Result => LoadFromFile: %d\n", LoadFromFile());
    fprintf(stdout, "Result => LoadFromMemory: %d\n", LoadFromMemory());

    return 0;
}
