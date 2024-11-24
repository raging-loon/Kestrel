#ifndef SENSOR_DATA_SOURCE_H_
#define SENSOR_DATA_SOURCE_H_

#include <libkds/kds_mod.h>
#include <libkds/kds_err.h>

#include <string>
#include <memory>

namespace kestrel 
{

class DataSourceHandle;

using dsHandle = void*;

///
/// @brief 
///     Wrapper around a data source module
///
class DataSource 
{
public:

    DataSource() : m_ds(nullptr) {}

    kds_error loadModule(const std::string& filename);

    const char* getName() const 
    { 
        return (m_ds && m_ds->name) 
                    ? m_ds->name 
                    : "invalid module"; 
    }

    std::unique_ptr<DataSourceHandle> createHandle();

private:
    /// Non owning pointer to data source module data
    kds_module_t*     m_ds;

};


///
/// @brief 
///     RAII wrapper around a handle from a data source
/// @details
///     You should not construct this yourself, instead rely on the
///     appropriate @ref DataSource module
///     
///     The order of initialization is as follows:
///       1. Object constructed
///       2. Call @ref setConfig() if there is configuration to set
///       3. Call @ref prepareHandle() to finalize the handle
///
class DataSourceHandle
{
public:

    explicit DataSourceHandle(const kds_module_t* const mod);
    ~DataSourceHandle();

    kds_error setConfig(const char* cfgStr);    

    kds_error prepareHandle();

private:
    /// non-owning pointer to the data source that spawned our handle
    const kds_module_t* const m_dataSource;

    /// handle to our instance
    dsHandle handle;

};


} // kestrel


#endif // SENSOR_DATA_SOURCE_H_