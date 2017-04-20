//
// Created by brout_m on 18/04/17.
//

#ifndef CPP_PLAZZA_ICORE_HPP
#define CPP_PLAZZA_ICORE_HPP

namespace plazza
{
    class ICore
    {
    public:
        virtual ~ICore(){};
        virtual void initialize(int ac, char **av, char **env) = 0;
        virtual int run() = 0;
    };
}

#endif //CPP_PLAZZA_ICORE_HPP
