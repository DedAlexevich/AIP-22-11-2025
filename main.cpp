#include <iostream>

class Ints {
public:
  Ints();

  Ints(size_t s, int c) : k(s), data(s ? new int[s]{} : nullptr)
  {
    for (size_t i = 0; i < s; i++) {
      data[i] = c;
    }
  }

  Ints(const Ints& c);
  Ints(Ints&& c)  : k(c.k), data(c.data)
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
  size_t k;
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
  size_t sizePoints();
  Points append(p_t a) const;
  Points append(const Points& w) const;
};

Points::Points(size_t k, p_t a) : data(k*2, a.x)
{
  for (size_t i = 0; i < k; ++i) {
    data.set(i*2 + 1, a.y);
  }
}

size_t Points::sizePoints()
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

Points Points::append(const Points& w) const
{
  Ints delta(w.data);
  delta = data.append(delta);
  return Points(std::move(delta));
}







int main()
{
  Points a(2, p_t{1,2});
  p_t z {3, 4};
  Points b(a);
  Points c = a.append(b);

  std::cout << "CHECK\n" << a.sizePoints();

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
  r.data = new int[k+1];
  for (size_t i = 0; i < k; ++i) {
    r.data[i] = data[i];
  }
  r.data[k] = v;
  r.k = k+1;
  return r;
}

Ints::Ints() : k(0), data(nullptr)
{}

Ints::Ints(const Ints& c) : k(c.k), data(c.k ? new int[c.k] : nullptr)
{
  if (c.k) {
    for (size_t i = 0; i < c.k; ++i) {
      data[i] = c.data[i];
    }
  }
}

Ints& Ints::operator=(const Ints& i)
{
  int* r = nullptr;
  if (i.k) {
    r = new int[i.k];
    for (size_t j = 0; j < i.k; ++j) {
      r[j] = i.data[j];
    }
  }
  delete[] data;
  data = r;
  k = i.k;
  return *this;
}

Ints& Ints::operator=(Ints&& i)
{
  if (this != &i) {
    delete[] data;
    data = i.data;
    k = i.k;
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
  return k;
}

int Ints::get(size_t id) const
{
  return data[id];
}

void Ints::set(size_t id, int v)
{
  data[id] = v;
}

