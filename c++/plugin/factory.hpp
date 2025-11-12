#pragma once

#include "iplugin.hpp"
#include <unordered_map>

class PluginFactory
{
    PluginFactory() = default;
    PluginFactory(const PluginFactory &) = delete;
    PluginFactory & operator=(const PluginFactory &) = delete;

public:
    static PluginFactory & getInstance()
    {
        static PluginFactory instance;
        return instance;
    }   

    static void add_plugin_to_factory(const std::string &id, std::unique_ptr<IPlugin> pluginObj)
    {
        pluginRegistry[id] = std::move(pluginObj);
    }

    static std::unique_ptr<IPlugin> createPlugin(const std::string &pluginType)
    {
        if (pluginRegistry.find(pluginType) != pluginRegistry.end())
        {
            return pluginRegistry[pluginType]->clone();
        }
        return nullptr;
    }

    static void stopAllPlugins()
    {
        for (auto & [id, plugin] : pluginRegistry)
        {
            plugin->stop();
        }
    }
private:
    inline static std::unordered_map<std::string, std::unique_ptr<IPlugin>> pluginRegistry;
  
};