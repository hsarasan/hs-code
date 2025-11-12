#pragma once

#include "iplugin.hpp"
#include <iostream>
#include <vector>
#include "registrar.hpp"

struct Printer : public IPlugin
{
    std::unique_ptr<IPlugin> clone() const override
    {
        return std::make_unique<Printer>(*this);
    }

    void start() override
    {
        std::cout<<"Printer Plugin started."<<std::endl;
    }

    void stop() override
    {
        std::cout<<"Printer Plugin stopped."<<std::endl;
    }

    void execute(const Context &ctx) override
    {
        std::cout << "Printer: " << ctx.data << std::endl;
    }
    std::vector<std::string> getSupportedActions() const override
    {
        return {"print"};
    }
};

struct Painter : public IPlugin
{
    std::unique_ptr<IPlugin> clone() const override
    {
        return std::make_unique<Painter>(*this);
    }

    void start() override
    {
        std::cout<<"Painter Plugin started."<<std::endl;
    }

    void stop() override
    {
        std::cout<<"Painter Plugin stopped."<<std::endl;
    }

    void execute(const Context &ctx) override
    {
        std::cout << "Drew: " << ctx.data << std::endl;
    }
    std::vector<std::string> getSupportedActions() const override
    {
        return {"draw"};
    }
};

REGISTER_PLUGIN("printer", Printer);
REGISTER_PLUGIN("painter", Painter);