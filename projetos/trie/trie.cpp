#include "trie.h"
#include <stdexcept>
#include <iostream>

Trie::Trie(unsigned alphabetSize)
    : amountOfKeysStored(0)
{
  TrieNode::alphabetSize = alphabetSize;
}

bool Trie::search(const std::string key)
{
  /* Não são permitidas buscas nulas */
  if (key.empty())
    throw std::invalid_argument("The string must have some chars");

  /* chama o método recursivo get que fará a busca na árvore */
  TrieNode *x = get(trieRoot, key, 0);

  /* Chave não encontrada */
  if (x == nullptr)
    return false;

  /* se isLeaf == true então a chave foi encontrada */
  return true;
}

void Trie::buscarPrefixo(const std::string prefixo)
{
  /* Não são permitidas buscas nulas */
  if (prefixo.empty())
    throw std::invalid_argument("The string must have some chars");

  char *palavra = (char *)calloc(256, sizeof(char));
  bool res = buscarPrefixoNo(trieRoot, prefixo, palavra, 0);

  /* Chave não encontrada */
  if (!res)
    std::cout << "Prefixo \"" << prefixo << "\" não encontado!";

  free(palavra);
}

bool Trie::buscarPrefixoNo(TrieNode *x, const std::string prefixo, char *palavra, int trieLevel)
{
  /* Nó nulo a chave não se encontra na árvore */
  if (x == nullptr)
    return false;

  /*
   * Se a profundidade da árvore (trieLevel) for igual a quantidade de caracteres
   * (key.length()) então a chave tem um cadidato a "hit" se este nó for uma folha
   * (isLeafe() == true) então se tem um "hit" se não se tem um "miss"
   */
  if (trieLevel == prefixo.length())
  {
    escrevePalavra(x, palavra, trieLevel);
    return true;
  }

  /*
   * Elemento não encontrado, recupera o próximo caractere e reinicia as
   * verificações com uma chamada recursiva
   */
  unsigned char c = prefixo[trieLevel];
  palavra[trieLevel] = c;
  return buscarPrefixoNo(x->arrSubTries[c], prefixo, palavra, trieLevel + 1);
}

void Trie::escrevePalavra(TrieNode *x, char *palavra, int trieLevel)
{
  for (int i = 0; i < TrieNode::alphabetSize; i++)
    if (x->arrSubTries[i])
    {
      palavra[trieLevel] = i;
      escrevePalavra(x->arrSubTries[i], palavra, trieLevel + 1);
    }

  if (x->isLeaf)
  {
    palavra[trieLevel] = '\0';
    std::cout << palavra << std::endl;
  }
}

TrieNode *Trie::get(TrieNode *x, const std::string key, int trieLevel)
{
  /* Nó nulo a chave não se encontra na árvore */
  if (x == nullptr)
    return nullptr;

  /*
   * Se a profundidade da árvore (trieLevel) for igual a quantidade de caracteres
   * (key.length()) então a chave tem um cadidato a "hit" se este nó for uma folha
   * (isLeafe() == true) então se tem um "hit" se não se tem um "miss"
   */
  if (trieLevel == key.length())
  {
    if (x->isLeaf)
      return x;
    else
      return nullptr;
  }

  /*
   * Elemento não encontrado, recupera o próximo caractere e reinicia as
   * verificações com uma chamada recursiva
   */
  unsigned char c = key[trieLevel];
  return get(x->arrSubTries[c], key, trieLevel + 1);
}

void Trie::insert(const std::string key)
{
  /* Não são permitidas inserções nulas */
  if (key.empty())
    throw std::invalid_argument("The string must have some chars");

  /* chama o método recursivo add que fará a inserção na árvore */
  trieRoot = add(trieRoot, key, 0);
}

TrieNode *Trie::add(TrieNode *x, const std::string key, int trieLevel)
{
  /*
   * Se o nó é nulo então a chave completa não está na árvore, é necessário criar
   * um novo nó para alocar tal caractere, perceba que este nó deve ser do tamanho
   * do alfabeto adotado
   */
  if (x == nullptr)
  {
    x = new TrieNode();
    x->setAlphabetSize(TrieNode::alphabetSize);
  }

  /*
   * Se a profundidade da árvore (trieLevel) for igual a quantidade de caracteres
   * (key.length()) então a chave está completa dentro da árvore;
   */
  if (trieLevel == key.length())
  {

    /*
     * Há que se verificar se a chave encontrada NÃO é uma folha. Caso NÃO seja
     * incrementa o indicador de quantidade de chaves armazenadas
     */
    if (!x->isLeaf)
    {
      this->amountOfKeysStored++;
    }

    /* Marca como folha */
    x->isLeaf = true;

    /* Retorna a folha inserida */
    return x;
  }

  /*
   * Se a profundidade da árvore (trieLevel) ainda não for igual a quantidade de
   * caracteres (key.length()) então prepara uma chamada recursiva para
   * verficação/criação de um novo nó
   */
  unsigned char c = key[trieLevel];
  x->arrSubTries[c] = add(x->arrSubTries[c], key, trieLevel + 1);

  /* Retorna a folha inserida */
  return x;
}

void Trie::deleteNode(const std::string key)
{

  /* Não são permitidas inserções nulas */
  if (key.empty())
    throw std::invalid_argument("The string must have some chars");

  /* chama o método recursivo get que fará a remoção na árvore */
  trieRoot = deleteNode(trieRoot, key, 0);
}

TrieNode *Trie::deleteNode(TrieNode *x, std::string key, int trieLevel)
{

  /* Nó nulo a chave não se encontra na árvore */
  if (x == nullptr)
    return nullptr;

  /*
   * Se a profundidade da árvore (trieLevel) for igual a quantidade de caracteres
   * (key.length()) então a chave tem um cadidato a remoção.
   */
  if (trieLevel == key.length())
  {
    /*
     * Se este nó for uma folha (isLeafe() == true) então o nó é desmarcado como
     * folha e a contagem de item da trie é decrementada
     */
    if (x->isLeaf)
      amountOfKeysStored--;

    x->isLeaf = false;
  }
  else
  {

    /*
     * Se a profundidade da árvore (trieLevel) ainda não for igual a quantidade de
     * caracteres (key.length()) então prepara uma chamada recursiva para
     * verficação/remoção de próximo nó
     */
    unsigned char c = key[trieLevel];
    x->arrSubTries[c] = deleteNode(x->arrSubTries[c], key, trieLevel + 1);
  }

  /*
   * Na volta das chamadas recursivas, no momento em que uma folha for encontrada a
   * deleção da árvore é terminada retornando-se um nó válido
   */
  if (x->isLeaf)
    return x;

  /*
   * Se o nó não é valido, anula todos os nós abaixo deste e, em seguinda, retorna
   * um endereço nulo para o nivel acima
   */
  for (int i = 0; i < TrieNode::alphabetSize; i++)
    if (x->arrSubTries[i] != nullptr)
      return x;

  delete x;
  return nullptr;
}