#include "factory.hpp"
#include <iostream>
#include "iplugin.hpp"
#include "plugins.hpp"
#include "plugin_manager.hpp"

int main(){
    // plugins are auto-registered; use the manager singleton
    PluginManager &manager = PluginManager::getInstance();
    // optionally add by type at runtime: manager.addPlugin("printer");
    Context ctx{"Hello, World!"};
    manager.executeAction("print", ctx);
    manager.executeAction("nonexistent_action", ctx);
    Context painting{"My beautiful landscape"};
    manager.executeAction("draw", painting);

    return 0;
}