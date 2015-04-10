#include <iostream>

// Convert void * parameter to uintptr_t
template <typename T>
struct ParamTrait {
  typedef T Type;
};

template <>
struct ParamTrait<void *> {
  typedef uintptr_t Type;
};

void foo(void *p) {

}

// Construct a template to generate a wrapper function for foo, replace void * by
// uintptr_t.
template <typename R>
struct FooWrapper;

template <typename R, typename P0>
struct FooWrapper<R (*)(P0)> {
  typedef typename ParamTrait<P0>::Type P0_TYPE;

  R call(P0_TYPE p0) {
    P0 cvt = reinterpret_cast<P0>(p0);
    foo(cvt);
  }
};

int main() {
  FooWrapper<void (*)(void *)> fw;
  uintptr_t fake_param = 0;
  fw.call(fake_param);

  return 1;
}
