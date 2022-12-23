#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "trienode.h"

class Trie
{
public:
  TrieNode *trieRoot = nullptr; // root of trie
  int amountOfKeysStored;       // number of keys in trie

public:
  Trie(unsigned alphabetSize);
  bool search(const std::string key);
  void buscarPrefixo(const std::string prefixo);
  void insert(std::string key);
  void deleteNode(std::string key);

private:
  TrieNode *get(TrieNode *x, const std::string key, int trieLevel);
  TrieNode *add(TrieNode *x, const std::string key, int trieLevel);
  TrieNode *deleteNode(TrieNode *x, const std::string key, int trieLevel);
  bool buscarPrefixoNo(TrieNode *x, const std::string prefixo, char *palavra, int trieLevel);
  void escrevePalavra(TrieNode *x, char *palavra, int trieLevel);
};
#endif // TRIE_H