#pragma once

#include<vector>
#include "Wrapper.h"


class Engine {
public:
    using Mtype = std::function<int(const std::unordered_map<std::string, int>&)>;

    template<typename T, typename... Args>
    void register_command(Wrapper<T, Args...>* wrapper, const std::string& command) {
        if (!wrapper) throw std::runtime_error("error: invalid wrapper");

        wrappedCommands[command] = [wrapper](const std::unordered_map<std::string, int>& args)
        {
            return wrapper->executeWrapped(args);
        };
    }

	int execute(const std::string& command, const std::unordered_map<std::string, int>& args) {
        auto it = wrappedCommands.find(command);
        if (it != wrappedCommands.end())
        {
            return it->second(args);
        }
        else
        {
            throw std::runtime_error("error: invalid command " + command);
        }
	};
private:
    std::unordered_map<std::string, Mtype> wrappedCommands;
};
