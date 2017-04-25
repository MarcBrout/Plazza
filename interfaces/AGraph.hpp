//
// Created by duhieu_b on 13/04/17.
//

#ifndef CPP_PLAZZA_IGRAPH_HPP
#define CPP_PLAZZA_IGRAPH_HPP

#include <vector>
#include <cstddef>
#include <map>
#include <algorithm>
#include "Enums.hpp"

template <typename T, typename U>
class AGraphAst
{
public:
    struct s_node
    {
        std::pair<T , U>            s_data;
        std::vector<AGraphAst<T, U>::s_node>  s_link;
        s_node(std::pair<T, U> c_data) : s_data(c_data) {}
        bool operator==(AGraphAst<T, U>::s_node const& eq) const
        {
            return s_data.first == eq.s_data.first && s_data.second == eq.s_data.second;
        }
        bool operator!=(AGraphAst<T, U>::s_node const& eq) const
        {
            return s_data.first != eq.s_data.first && s_data.second != eq.s_data.second;
        }
    };

private:
    std::vector<AGraphAst<T, U>::s_node> m_graph;
    std::vector<AGraphAst<T, U>::s_node> m_stock;

    void run_graph(int count, std::pair<T, U> const &comp, AGraphAst<T, U>::s_node cur, AGraphAst<T, U>::s_node test)
    {
        typename std::vector<AGraphAst<T, U>::s_node>::iterator it;

        if ((it = std::find(cur.s_link.begin(), cur.s_link.end(), test)) == cur.s_link.end())
        {
            return;
        }
        if (it->s_data == comp && !count)
        {
            cur.s_link.erase(it);
            return;
        }
        if (*it == cur.s_link.back())
        {
            if (cur.s_link.begin()->s_link.size() == 0)
                return ;
            run_graph(count, comp, *(cur.s_link.begin()), *(cur.s_link.begin()->s_link.begin()));
        }
        else
            run_graph(count, comp, cur, *(it + 1));
    }

public:
    AGraphAst(T c_id, U c_type)
    {
        AGraphAst<T, U>::s_node l_newnode(std::pair<T, U>(c_id, c_type));
        m_graph.push_back(l_newnode);
    }

    void addNode(T p_id, U p_type)
    {
        AGraphAst<T, U>::s_node l_newNode(std::pair<T, U>(p_id, p_type));
        m_stock.push_back(l_newNode);
    }

    void simpleLinkNode(T p_id)
    {
        for (AGraphAst<T, U>::s_node &node : m_stock)
        {
            if (node.s_data.first == p_id)
            {
                int i(0);
                for (AGraphAst<T, U>::s_node &type : m_stock)
                {
                    if (type.s_data.first != p_id)
                    {
                        node.s_link.push_back(type);
                        m_stock.erase(m_stock.begin() + i);
                        break;
                    }
                    i++;
                }
                break;
            }
        }
    }

    bool validNode()
    {
        if (m_stock.size() != 1)
            return false;
        m_graph.begin()->s_link.push_back(m_stock.back());
        m_stock.erase(m_stock.begin());
        return true;
    }

    void deleteNode(T p_id, U p_type, int count = 0)
    {
        run_graph(count, std::pair<T, U>(p_id, p_type), *(m_graph.begin()), *(m_graph.begin()->s_link.begin()));
    }

    void clear()
    {
        m_graph.clear();
    }

    std::vector<AGraphAst<T, U>::s_node> &getGraph()
    {
        return m_graph;
    }

    void clear()
    {
        m_graph.clear();
        m_stock.clear();
    }
};

#endif //CPP_PLAZZA_IGRAPH_HPP
