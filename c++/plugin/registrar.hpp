#pragma once

#include "factory.hpp"
#include "plugin_manager.hpp"
#include <memory>

// Registrar: registers a prototype plugin instance with the factory during static init
template <typename PluginT>
struct PluginRegistrar
{
    PluginRegistrar(const std::string &id)
    {
        auto proto = std::make_unique<PluginT>();
        PluginFactory::add_plugin_to_factory(id, std::move(proto));
        // create another instance for manager
        auto instance = PluginFactory::createPlugin(id);
        if (instance)
            PluginManager::getInstance().addPlugin(std::move(instance));
    }
};

#define REGISTER_PLUGIN(ID, TYPE) static PluginRegistrar<TYPE> registrar_##TYPE(ID);
