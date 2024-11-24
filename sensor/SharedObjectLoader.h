#ifndef SENSOR_SHARED_OBJECT_LOADER_H_
#define SENSOR_SHARED_OBJECT_LOADER_H_


namespace kestrel 
{

#ifdef __linux__
#include <dlfcn.h>
#elif defined(WIN64) || defined(WIN32)
#include <windows.h>
#else 
# error "Invalid Architecture"
#endif

namespace SharedObjectLoader 
{

#ifdef __linux__

template <class Fn>
Fn* load(const char* libName, const char* objName)
{
    void* libHandle = dlopen(libName, RTLD_LAZY);
    if(!libHandle)
        return nullptr;
    
    Fn* obj = static_cast<Fn*>(dlsym(libHandle, objName));

    return obj;
}

const char* getSOAPIError() { return dlerror(); }

#endif 


} // SharedObjectLoader

} // kestrel

#endif // SENSOR_SHARED_OBJECT_LOADER_H_