//
// Created by brout_m on 20/04/17.
//

#ifndef CPP_PLAZZA_FORKER_HPP
#define CPP_PLAZZA_FORKER_HPP

#include <functional>
#include <unistd.h>

namespace plazza
{
    template <typename ...Args>
    class Forker
    {
    public:
        int create_child(std::function<void(Args...)> fn, Args... args)
        {
            pid_t l_pid;

            l_pid = fork();
            if (l_pid == 0)
            {
                fn(args...);
            }
            else if (l_pid > 0)
            {
              return (0);
            }
            return (1);
        };

        bool operator()(std::function<void(Args...)> fn, Args... args)
        {
            return create_child(fn, args...);
        };
    };
}

#endif //CPP_PLAZZA_FORKER_HPP
