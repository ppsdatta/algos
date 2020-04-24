#include <iostream>
#include <string>

template <typename T>
struct node
{
  T v;
  node *next;

  node(T v)
  {
    this->v = v;
    this->next = nullptr;
  }

  node(T v, node *next)
  {
    this->v = v;
    this->next = next;
  }
};


template <typename T>
node<T> *add_to_node(node<T> *n, const T& v)
{
  if (n == nullptr) {
    return new node<T>{v};
  }

  n->next = add_to_node(n->next, v);

  return n;
}


template <typename T>
void free_node(node<T> *n)
{
  if (n != nullptr)
    free_node(n->next);
  delete n;
}


template <typename T>
void print_node(node<T> *n)
{
  using std::cout;
  using std::endl;

  
  if (n == nullptr)
    cout << "[]";
  else
    for (node<T> *in = n; in != nullptr; in = in->next) {
      cout << in->v << endl;
    }
}


template <typename T>
node<T> *reverse_node(node<T> *n)
{
  if (n == nullptr || n->next == nullptr) return n;

  node<T> *p, *q, *r;

  p = n;
  q = n->next;

  for (;;) {
    r = q->next;
    q->next = p;

    if (r == nullptr) {
      q->next = p;
      break;
    }

    p = q;
    q = r;
  }

  n->next = nullptr;
  
  return q;
}


template <typename T>
node<T> *add_to_front_node(node<T> *n, T v)
{
  auto new_node = new node<T>{v};
  new_node->next = n;
  
  return new_node;
}


template <typename T>
node<T> *add_node_at(node<T> *n, size_t idx, T v)
{
  if (idx == 0) 
    return add_to_front_node(n, v);
  
  node<T> *itn = n;
  for (size_t i = 0; i < idx - 1; ++i) {
    if (itn == nullptr)
      return n;

    itn = itn->next;
  }

  node<T> *new_node = new node<T>{v};
  new_node->next = itn->next;
  itn->next = new_node; 
  
  return n;
}


template <typename T>
node<T> *middle_node(node<T> *n)
{
  node<T> *i = n;
  int count = 0;

  while (i != nullptr) {
    if (count == 2) {
      n = n->next;
      count = 0;
    }
    
    i = i->next;
    count++;
    
  }

  return n;
}
  

int main()
{
  node<int> *n = nullptr;

  n = add_to_node(n, -11);
  n = add_to_node(n, 1);
  n = add_to_node(n, 2);
  n = add_to_node(n, 3);
  n = add_to_node(n, 11);
  n = add_to_node(n, 11);
  n = add_to_node(n, 13);
  
  print_node(n);
  std::cout << "----\n";
  n = reverse_node(n);
  print_node(n);
  std::cout << "----\n";
  std::cout << middle_node(n)->v << std::endl;

  free_node(n);

  node<std::string> *s = nullptr;
  s = add_to_node(s, std::string{"resistance"});
  s = add_to_node(s, std::string{"enlightened"});
  s = add_to_node(s, std::string{"motoko"});
  s = add_to_node(s, std::string{"kusanagi"});
 
  print_node(s);
  std::cout << "-----\n";
  s = reverse_node(s);
  print_node(s);
  std::cout << "-----\n";
  std::cout << middle_node(s)->v << std::endl;
  std::cout << "-----\n";
  s = add_to_front_node(s, std::string{"Ghost"});
  print_node(s);
  std::cout << "-----\n";
  s = add_node_at(s, 0, std::string{"Shell"});
  print_node(s);
  std::cout << "-----\n";
  s = add_node_at(s, 1, std::string{"Bataou"});
  print_node(s);
  std::cout << "-----\n";
  s = add_node_at(s, 6, std::string{"Saito"});
  print_node(s);
  std::cout << "-----\n";
  s = add_node_at(s, 8, std::string{"Rang"});
  print_node(s);

  free_node(s);

  return 0;
}

