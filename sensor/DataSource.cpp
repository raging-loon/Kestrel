#include "DataSource.h"
#include <SharedObjectLoader.h>
#include <cstring>

using kestrel::DataSource;
using kestrel::DataSourceHandle;


std::unique_ptr<DataSourceHandle> DataSource::createHandle()
{
    if(!m_ds)
        return nullptr;
    
    return std::make_unique<DataSourceHandle>(m_ds);
}


kds_error DataSource::loadModule(const std::string& filename) 
{
    m_ds = SharedObjectLoader::load<kds_module_t>(filename.c_str(), KDS_MOD_NAME_STR);
    if(!m_ds) 
    {
        printf("Failed to load: %s\n", SharedObjectLoader::getSOAPIError());
        return KDS_INIT_FAIL;
    }
    return KDS_OK;
}


DataSourceHandle::DataSourceHandle(const kds_module_t* const mod)
    : m_dataSource(mod), handle(nullptr)
{
    if(!m_dataSource)
        return;

    if(m_dataSource->instantiate(static_cast<void**>(&handle)) != KDS_OK)
        return;

}

DataSourceHandle::~DataSourceHandle()
{
    if(handle && m_dataSource)
        m_dataSource->unload(handle);
    handle = nullptr;
}

kds_error DataSourceHandle::setConfig(const char* cfgStr)
{
    if(!cfgStr)
        return KDS_INVALID_PARAM;

    return m_dataSource->parse_config(
        handle, 
        cfgStr,
        strlen(cfgStr)
    );

}

kds_error DataSourceHandle::prepareHandle()
{
    return m_dataSource->load(handle);
}
