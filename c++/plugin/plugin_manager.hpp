#pragma once

#include "iplugin.hpp"
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class PluginManager
{
public:
    PluginManager() = default;
    static PluginManager & getInstance();

    void addPlugin(std::unique_ptr<IPlugin> plugin);
    void addPlugin(const std::string &pluginType);

    void executeAction(const std::string &action, const Context &ctx);

    ~PluginManager();
private:
    std::vector<std::unique_ptr<IPlugin>> plugins;
    std::unordered_map<std::string, size_t> action_to_id;
};