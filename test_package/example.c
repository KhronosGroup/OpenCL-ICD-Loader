#if defined(_WIN32)
    #define CL_API_ENTRY
    #define CL_API_CALL     __stdcall
    #define CL_CALLBACK     __stdcall
#else
    #define CL_API_ENTRY
    #define CL_API_CALL
    #define CL_CALLBACK
#endif

CL_API_ENTRY void *CL_API_CALL clGetExtensionFunctionAddress(char const *);

int main(void) {
	void * (CL_API_CALL *KHRpfn_clGetExtensionFunctionAddress)(const char *) = 
	        clGetExtensionFunctionAddress;
	return 0;
}
