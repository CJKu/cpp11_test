#include <iostream>

template <typename U, typename V>
class A {
public:
  U mU;
  V mV;
};

template <typename T,
         template <typename, typename> class CONT>
class B {
public:
  CONT<T, T> mA;
};

template <typename T>
T foo(T v)
{
  return ++v;
}

template <typename T>
class Generic {
public:
  void foo()
  {
    std::cout << "Generic::foo" << std::endl;
  }
};

template <>
void Generic<int>::foo() {
  std::cout << "Generic<int>::foo" << std::endl;
}

// Full specilization
template <>
class Generic<double> {
public:
  void foo();
};

void Generic<double>::foo() {
  std::cout << "Generic<double>::foo" << std::endl;
}

void FooOverload() {

}

int FooOverload(int i) {
  std::cout << "FooOverload(" << i << ")" << std::endl;
  return 1;
}

int main() {
  B<int, A> b;

  int v1 = 0;
  int v2 = foo(v1);
  std::cout << "v2 = " << v2 << std::endl;

  // Generic template
  Generic<float> g1;
  g1.foo(); // Generic::foo
  Generic<int> g2;
  g2.foo(); // Generic<int>::foo
  // Full specialization template
  Generic<double> g3;
  g3.foo(); // Generic<double>::foo

  return 0;
}
