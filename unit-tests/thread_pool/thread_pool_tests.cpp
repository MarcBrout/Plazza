//
// Created by brout_m on 16/04/17.
//

#include "gtest/gtest.h"
#include "ThreadPool.hpp"


typedef std::pair<std::string, plazza::Information > order_t;
typedef std::vector<std::string> result_t;

void read_order(threadpool::ThreadPool<order_t, result_t>::data &data)
{
 //   int id {getpid()};
    order_t order;

    while (!data.s_over)
    {
        if (data.s_orderQ.pop(&order))
        {
/*            std::cout << "thread n°" << id
                      << " pushing : " << order.first << std::endl; */

            std::vector<std::string> coucou;
            coucou.push_back(order.first + " IS ");
            switch (order.second)
            {
                case (plazza::Information::PHONE_NUMBER) : coucou[0] += "PHONE NUMBER";
                    break;
                case (plazza::Information::EMAIL_ADDRESS) : coucou[0] += "EMAIL ADDRESS";
                    break;
                case (plazza::Information::IP_ADDRESS) : coucou[0] += "IP ADDRESS";
                    break;
            }

            data.s_resultQ.push(std::move(coucou));
            data.s_resultQ.signal();
        }
        usleep(1000);
    }
}

TEST(thread_pool_test, full_test)
{
    threadpool::ThreadPool<order_t, result_t>       l_threadPool(10);
    threadpool::SafeQ<std::vector<std::string>>     &l_resQ = l_threadPool.getResults();
    std::vector<std::vector<std::string>>           l_vecres;
    bool                                            end_test { false };
    std::vector<std::string>                        res;
    int                                             i(0);

    l_threadPool.run(read_order);

    while (!end_test)
    {
        l_threadPool.pushAction(order_t("test", static_cast<plazza::Information >(rand() % 3)));
        usleep(rand() % 100000 + 100000);
        if (i == 49)
            end_test = true;
        ++i;
    }

    while (l_resQ.size())
    {
        if (l_resQ.tryPop(&res))
            l_vecres.push_back(res);
    }

    ASSERT_EQ(l_vecres.size(), 50);
/*
    int k(0);
    int j(0);

    for (std::vector<std::string> &vecs : l_vecres)
    {
        for (std::string &str : vecs)
        {
            std::cout << "Result n°(" << k << "," << j << ") = " << str << std::endl;
            j++;
        }
        k++;
    }
*/
    l_threadPool.setOver(true);
}