#pragma once

#include <memory>
#include <string>
#include <vector>

struct Context
{
    std::string data;
};


class IPlugin
{
public:
    virtual std::unique_ptr<IPlugin> clone() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void execute(const Context &) = 0;
    virtual ~IPlugin() = default;
    virtual std::vector<std::string> getSupportedActions() const = 0;
};
