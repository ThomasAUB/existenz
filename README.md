[![Build Status](https://app.travis-ci.com/ThomasAUB/existenz.svg?branch=main)](https://travis-ci.com/ThomasAUB/existenz)



# Existenz


Single header file providing compile-time checks of existence of members.
Works with member functions, static member functions, members and static members.


## Example

```cpp

// generate a "exz::static_member_function_call" class
STATIC_MEMBER_FUNCTION(call);

struct B {
    static void call() {
        // ...
    }
};

struct C {};

template<typename... T>
struct A {

    A() {
        (call<T>(), ...);
    }

    template<typename _T>
    void call() {

        // test if type contains a "static void call()" function
        if constexpr (exz::static_member_function_call::exists<_T, void, void>()) {
            _T::call();
        }

    }

};


A<B, C> sA;


```
