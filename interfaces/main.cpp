//
// main.cpp for main in /home/duhieu_b/CPP/cpp_plazza/interfaces
//
// Made by duhieu_b
// Login   <benjamin.duhieu@epitech.eu>
//
// Started on  Tue Apr 18 14:08:15 2017 duhieu_b
// Last update Tue Apr 18 14:19:38 2017 duhieu_b
//

#include "AGraph.hpp"
#include "Enums.hpp"

int main()
{
  AGraphAst <plazza::Type, std::string>graph(plazza::COMMA, ";");

  graph.addNode(plazza::ORDER, "PHONE_NUMBER");
  graph.addNode(plazza::FILE, "index.htm");
  graph.addNode(plazza::FILE, "company.csv");
  graph.simpleLinkNode(plazza::ORDER);
  graph.simpleLinkNode(plazza::ORDER);
  graph.validNode();
  return (0);
}
