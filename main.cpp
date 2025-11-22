#include <iostream>


class Ints {
public:
  Ints();
  Ints(int v) : n(v), data(new int[v]{}) {}
  Ints(const Ints& c);
  Ints(Ints&& c)  : n(c.n), data(c.data)
  {
    c.data = nullptr;
  }
  Ints& operator=(const Ints& i);
  Ints& operator=(Ints&& i);
  ~Ints();
  size_t size() const;
  int get(size_t id) const;
  void set(size_t id, int v);
  Ints append(const Ints& arr) const;

  Ints append(int v) const;

private:
  size_t n;
  int* data;
};

Ints Ints::append(const Ints& arr) const
{
  Ints r(*this);
  for (size_t i = 0; i < arr.size() ; ++i) {
    r = r.append(arr.get(i));
  }
  return r;
}

Ints Ints::append(int v) const
{
  Ints r;
  r.data = new int[n+1];
  for (size_t i = 0; i < n; ++i) {
    r.data[i] = data[i];
  }
  r.data[n] = v;
  r.n = n+1;
  return r;
}

inline Ints::Ints() : n(0), data(nullptr)
{}

inline Ints::Ints(const Ints& c) : n(c.n), data(c.n ? new int[c.n] : nullptr)
{
  if (c.n) {
    for (size_t i = 0; i < c.n; ++i) {
      data[i] = c.data[i];
    }
  }
}

inline Ints& Ints::operator=(const Ints& i)
{
  int* r = nullptr;
  if (i.n) {
    r = new int[i.n];
    for (size_t j = 0; j < i.n; ++j) {
      r[j] = i.data[j];
    }
  }
  delete[] data;
  data = r;
  n = i.n;
  return *this;
}

inline Ints& Ints::operator=(Ints&& i)
{
  if (this != &i) {
    delete[] data;
    data = i.data;
    n = i.n;
    i.data = nullptr;
  }
  return *this;
}

inline Ints::~Ints()
{
  delete[] data;
}

inline size_t Ints::size() const
{
  return n;
}

inline int Ints::get(size_t id) const
{
  return data[id];
}

inline void Ints::set(size_t id, int v)
{
  data[id] = v;
}



int main()
{
  Ints a(10);
  a = std::move(a);
  std::cout << "STATES\n";

}



