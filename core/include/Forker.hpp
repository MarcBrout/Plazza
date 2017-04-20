//
// Created by brout_m on 20/04/17.
//

#ifndef CPP_PLAZZA_FORKER_HPP
#define CPP_PLAZZA_FORKER_HPP

#include <functional>
#include <unistd.h>

namespace fork
{
    template <typename ...Args>
    class Forker
    {
    public:
        bool create_child(std::function<void(Args...)> fn, Args... args)
        {
            pid_t l_pid;

            l_pid = fork();
            if (!l_pid)
                return (true);
            else if (l_pid < 0)
                return (false);
            fn(args);
            std::exit(EXIT_SUCCESS);
        };

        bool operator()(std::function<void(Args...)> fn, Args... args)
        {
            return create_child(fn, args);
        };
    };
}

#endif //CPP_PLAZZA_FORKER_HPP
