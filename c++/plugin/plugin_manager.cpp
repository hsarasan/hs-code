#include "iplugin.hpp"
#include "factory.hpp"
#include "plugin_manager.hpp"
#include <iostream>

PluginManager &PluginManager::getInstance()
{
    static PluginManager instance;
    return instance;
}

void PluginManager::addPlugin(std::unique_ptr<IPlugin> plugin)
{
    const size_t id = plugins.size();
    auto actions = plugin->getSupportedActions();
    for (const auto &action : actions)
    {
        action_to_id[action] = id;
    }
    plugins.push_back(std::move(plugin));
}

void PluginManager::addPlugin(const std::string &pluginType)
{
    auto plugin = PluginFactory::createPlugin(pluginType);
    if (plugin)
    {
        addPlugin(std::move(plugin));
    }
    else
    {
        std::cout << "PluginFactory could not create plugin of type: " << pluginType << std::endl;
    }
}

void PluginManager::executeAction(const std::string &action, const Context &ctx)
{
    auto it = action_to_id.find(action);
    if (it != action_to_id.end())
    {
        size_t id = it->second;
        if (id < plugins.size() && plugins[id])
        {
            plugins[id]->execute(ctx);
        }
        else
        {
            std::cout << "No plugin instance for id: " << id << std::endl;
        }
    }
    else
    {
        std::cout << "No plugin found for action: " << action << std::endl;
    }
}

PluginManager::~PluginManager()
{
    PluginFactory::stopAllPlugins();
}