/*
** Linked_list
**
** By Pykos --]::::::>
**
** Source is a Open source !
** You can contact me by mail : eliott.martin@orange.fr
*/

#include <iostream>

/*
  ##README !##
  - For use the Generic_linked #include "Linked_list"
  - 3 kinds of fonctions : { "add", "remove", "get" }
  - For declare a new list :
	- Linked_list<"Votre type"> "Nom_de_votre_objet"
  (You can use every types)


  -Exemple :
#include <iostream>
#include "Linked_list.h"

typedef struct	test
{
int		nbr;
char		c;
}		Test;

int	main()
{
Linked_list<test>	ptr;
test			stock;
test			recup;

stock.nbr = 10;
stock.c = 'c';
ptr.addElement_start(stock);
ptr.getElement_start(recup);
std::cout << recup.nbr << std::endl;
std::cout << recup.c << std::endl;
return EXIT_SUCCESS;
}
*/

template<typename T> class Linked_list;

/* #!Class Node */
template <class T>
class Node
{
  friend class Linked_list<T>;

 private :

  Node();
  Node(const T & d);

  T		m_data;
  Node<T>	*m_next;
  Node<T>	*m_prev;
};

/* #!Constructeur Node */
template <typename T>
Node<T>::Node()
{
  m_prev = m_next = NULL;
}

template <typename T>
Node<T>::Node(const T & data_give)
{
  m_data = data_give;
  m_next = m_prev = NULL;
}


/* #!Class generic Linked_list */
template <typename T>
class Linked_list
{
 public:

  /* #!Constructeur */
  Linked_list();

  /* #!Destructeur */
  ~Linked_list();

  /* #!add */
  int	addElement_start(const T & data_give);
  int	addElement_end(const T & data_give);
  int	addElement_position(const T & data_give, int position);

  /* #!remove */
  int	removeElement_start();
  int	removeElement_end();
  int	removeElement_position(int position);
  int	removeElement_all();

  /* #!get */
  int	getElement_start(T & data_return) const;
  int	getElement_end(T & data_return) const;
  int	getElement_position(T & data_return, int position) const;
  inline int	getElement_size(void) const { return m_nbrNodes; }

 private:
  /* #!Node principale */
  Node<T>	*m_root;
  /* #!Nombre de Node dans la liste */
  int		m_nbrNodes;
};

/* #!Constructeur Linked_list */
template <typename T>
Linked_list<T>::Linked_list()
{
  m_root = new Node<T>;
  m_root->m_next = m_root;
  m_root->m_prev = m_root;
  m_nbrNodes = 0;
}

/* #!Destructeur Linked_list */
template <typename T>
Linked_list<T>::~Linked_list()
{
  delete m_root;
}

/* #!Function to add element */
template <typename T>
int	Linked_list<T>::addElement_start(const T & data_give)
{
  Node<T> *new_element;

  new_element = new Node<T>(data_give);
  if (!(new_element))
    return EXIT_FAILURE;
  new_element->m_prev = m_root;
  new_element->m_next = m_root->m_next;
  m_root->m_next->m_prev = new_element;
  m_root->m_next = new_element;
  ++m_nbrNodes;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::addElement_end(const T & data_give)
{
  Node<T> *new_element;

  new_element = new Node<T>(data_give);
  if (!(new_element))
    return EXIT_FAILURE;
  new_element->m_next = m_root;
  new_element->m_prev = m_root->m_prev;
  m_root->m_prev->m_next = new_element;
  m_root->m_prev = new_element;
  ++m_nbrNodes;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::addElement_position(const T & data_give, int position)
{
  Node<T>	*new_element;
  Node<T>	*element;
  int		index = 0;

  new_element = new Node<T>(data_give);
  element = m_root;
  if (!(new_element))
    return EXIT_FAILURE;
  if (position <= 0 || position >= m_nbrNodes)
    {
      position <= 0 ? addElement_start(data_give) : addElement_end(data_give);
      return EXIT_SUCCESS;
    }
  while (++index < position)
    element = element->m_next;
  new_element->m_prev = element;
  new_element->m_next = element->m_next;
  element->m_next->m_prev = new_element;
  element->m_next = new_element;
  ++m_nbrNodes;
  return EXIT_SUCCESS;
}

/* #!Function to remove element */
template <typename T>
int	Linked_list<T>::removeElement_start()
{
  Node<T>	*save;

  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  save = m_root->m_next;
  m_root->m_next = m_root->m_next->m_next;
  save->m_next->m_prev = m_root;
  delete save;
  --m_nbrNodes;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::removeElement_end()
{
  Node<T>	*save;

  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  save = m_root->m_prev;
  m_root->m_prev = m_root->m_prev->m_prev;
  save->m_prev->m_next = m_root;
  delete save;
  --m_nbrNodes;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::removeElement_position(int position)
{
  Node<T>	*save;
  int		index = -1;

  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  if (position <= 0 || position >= m_nbrNodes)
    {
      position <= 0 ? removeElement_start() : removeElement_end();
      return EXIT_SUCCESS;
    }
  save = m_root;
  while (++index != position)
    save = save->m_next;
  save->m_prev->m_next = save->m_next;
  save->m_next->m_prev = save->m_prev;
  delete save;
  --m_nbrNodes;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::removeElement_all()
{
  Node<T>	*tmp;
  Node<T>	*save;

  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  tmp = m_root->m_next;
  while (tmp != m_root)
    {
      save = tmp;
      tmp = tmp->m_next;
      delete save;
    }
  m_nbrNodes = 0;
  return EXIT_SUCCESS;
}

/* #!Function to give element */
template <typename T>
int	Linked_list<T>::getElement_start(T & data_return) const
{
  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  data_return = m_root->m_next->m_data;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::getElement_end(T & data_return) const
{
  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  data_return = m_root->m_prev->m_data;
  return EXIT_SUCCESS;
}

template <typename T>
int	Linked_list<T>::getElement_position(T & data_return, int position) const
{
  Node<T>	*element;
  int		index = -1;

  element = m_root;
  if (m_nbrNodes == 0)
    return EXIT_FAILURE;
  if (position <= 0 || position >= m_nbrNodes)
    {
      position <= 0 ? getElement_start(data_return) : getElement_end(data_return);
      return EXIT_SUCCESS;
    }
  while (++index < position)
    element = element->m_next;
  data_return = element->m_data;
  return EXIT_SUCCESS;
}
