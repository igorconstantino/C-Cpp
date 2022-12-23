#include "trie.h"
#include <iostream>

int main()
{
  Trie t(256);
  t.insert("amor");
  t.insert("amar");
  t.insert("amaranto");
  t.insert("amargo");
  t.insert("amigável");

  std::cout << t.search("amor") << std::endl;

  t.buscarPrefixo("am");

  t.deleteNode("amor");
  return 0;
}