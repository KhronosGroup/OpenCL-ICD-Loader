#ifndef _ICD_STRUCTS_H_
#define _ICD_STRUCTS_H_

typedef struct CLIicdDispatchTable_st  CLIicdDispatchTable;
typedef struct CLIplatform_st CLIplatform;

struct CLIicdDispatchTable_st
{
    void *entries[256];
    int entryCount;
};

#ifdef CL_ENABLE_ICD2

#define CL_OBJECT_BODY                                                         \
    CLIicdDispatchTable* dispatch;                                             \
    void* dispData

#define CL_INIT_OBJECT(obj, parent)                                            \
do                                                                             \
{                                                                              \
    obj->dispatch = parent->dispatch;                                          \
    obj->dispData = parent->dispData;                                          \
} while (0)

#define CL_INIT_PLATFORM(obj, table)                                           \
do                                                                             \
{                                                                              \
    obj->dispatch = table;                                                     \
    obj->dispData = NULL;                                                      \
} while (0)

#else //defined(CL_ENABLE_ICD2)

#define CL_OBJECT_BODY                                                         \
    CLIicdDispatchTable* dispatch

#define CL_INIT_OBJECT(obj, parent)                                            \
do                                                                             \
{                                                                              \
    obj->dispatch = parent->dispatch;                                          \
} while (0)

#define CL_INIT_PLATFORM(obj, table)                                           \
do                                                                             \
{                                                                              \
    obj->dispatch = table;                                                     \
} while (0)

#endif //defined(CL_ENABLE_ICD2)

struct CLIplatform_st
{
    CL_OBJECT_BODY;
};

#endif /* _ICD_STRUCTS_H_ */
