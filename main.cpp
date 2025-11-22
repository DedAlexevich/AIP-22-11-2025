#include <iostream>

class Ints {
public:
  Ints();
  Ints(size_t v, int a) : n(v), data(new int[v]{})
  {
    for (size_t i = 0; i < v; i++) {
      data[i] = a;
    }
  }
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

struct p_t {
  int x,y;
};

class Points {
  Ints data;
  Points(Ints&& a) : data(std::move(a))
  {}
public:
  Points() = default;
  Points(size_t k, p_t a);
  void set(size_t id, p_t a);
  p_t get(size_t id) const;
  size_t size();
  Points append(p_t a) const;
  Points append(const Points& w) const;
};

Points::Points(size_t k, p_t a) : data(k*2, a.x)
{
  for (size_t i = 0; i < k; ++i) {
    data.set(i*2 + 1, a.y);
  }
}

size_t Points::size()
{
  return data.size()/2;
}

void Points::set(size_t id, p_t a)
{
  data.set(id*2, a.x);
  data.set(id*2 + 1, a.y);
}

p_t Points::get(size_t id) const
{
  return p_t{data.get(id*2), data.get(id*2 + 1)};
}

Points Points::append(p_t a) const
{
  Ints delta(2, a.x);
  delta.set(1, a.y);
  delta = data.append(delta);
  return Points(std::move(delta));
}








int main()
{
  Points a(2, p_t{1,2});
  p_t z {3, 4};

  a = a.append(z);

  std::cout << "CHECK\n";

}

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

Ints::Ints() : n(0), data(nullptr)
{}

Ints::Ints(const Ints& c) : n(c.n), data(c.n ? new int[c.n] : nullptr)
{
  if (c.n) {
    for (size_t i = 0; i < c.n; ++i) {
      data[i] = c.data[i];
    }
  }
}

Ints& Ints::operator=(const Ints& i)
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

Ints& Ints::operator=(Ints&& i)
{
  if (this != &i) {
    delete[] data;
    data = i.data;
    n = i.n;
    i.data = nullptr;
  }
  return *this;
}

Ints::~Ints()
{
  delete[] data;
}

size_t Ints::size() const
{
  return n;
}

int Ints::get(size_t id) const
{
  return data[id];
}

void Ints::set(size_t id, int v)
{
  data[id] = v;
}

