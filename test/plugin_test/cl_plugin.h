#define PLUGIN_INIT plugin_init
#define XSTRING(x) TO_STRING(x)
#define TO_STRING(x) #x
#define PLUGIN_INIT_NAME XSTRING(PLUGIN_INIT)

#define PLUGIN_SUCCESS 0
#define PLUGIN_ERROR   1

typedef int plugin_init_fn(void);
typedef plugin_init_fn *plugin_init_pfn;
