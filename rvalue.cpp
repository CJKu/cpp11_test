#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int x;
int getInt()
{
  return x;
}

int && getRvalueInt()
{
  return std::move(x);
}

class A {
public:
  A(int v) : value(v)
  {
    cout << "A::ctor(" << value << ")" << endl;
  }
  A(const A &lhs): value(lhs.value)
  {
    cout << "A::copy-ctor(" << value << ")" << endl;
  }

  A operator+(const A& rhs) const
  {
    A tmp(*this);
    tmp.value += rhs.value;

    return tmp;
  }

  int value;
};

class B {
public:
  B(int v) : value(v)
  {
    cout << "B::ctor(" << value << ")" << endl;
  }
  B(B&& rhs) : value(rhs.value)
  {
    cout << "B::move-ctor(" << value << ")" << endl;
  }
  B(const B &lhs): value(lhs.value)
  {
    cout << "B::copy-ctor(" << value << ")" << endl;
  }

  B operator+(const B& rhs) const
  {
    B tmp(*this);
    tmp.value += rhs.value;

    return tmp;
  }

  int value;
};

B &&operator+(B &&rhs, const B &lhs)
{
  rhs.value = rhs.value + lhs.value;
  return std::move(rhs);
}

int main() {
  int &&v = getRvalueInt();
  v = 2;
  cout << "x = " << x << endl;

  A a1(1); // ctor(1)
  A a2(2); // ctor(2)
  A a3(3); // ctor(3)
  A asum = a1 + a2 + a3; // copy-ctor twice(a1+ a2/ temp + a3)

  B b1(1); // ctor(1)
  B b2(2); // ctor(2)
  B b3(3); // ctor(3)
  B bsun = b1 + b2 + b3; // copy-ctor(b1 + b2) move-ctor(temp + b3).
  return 0;
}
