![build status](https://github.com/ThomasAUB/existenz/actions/workflows/build.yml/badge.svg)
![license](https://img.shields.io/github/license/ThomasAUB/Existenz.svg)



# Existenz


Single header file providing compile-time checks of existence of members.
Works with member functions, static member functions, members and static members.


Provides detection for :

- member functions
- static member functions
- members

and operators such as :
- '()'
- '<'
- '>'
- '>='
- '<='
- '=='

## Member detection
```cpp
// macro generating a "exz::static_member_someFunction" class
MEMBER_FUNCTION(someFunction)

// true if the class SomeClassName has a member function
// called someFunction returning SomeReturnType and
// taking SomeArgType in argument
// false otherwise
constexpr bool result = exz::member_function_someFunction::exists<
    SomeClassName, // type of the class
    SomeReturnType, // function return type
    SomeArgType // argument type(s)
>();
```

## Operator detection
```cpp
// no need for generation macro for operators detection
constexpr bool result = 
exz::superior::exists<
    SomeClassName, // type of the class
    SomeReturnType // operator return type
>();
```

## Example

```cpp
// generate a "exz::static_member_function_call" class
STATIC_MEMBER_FUNCTION(call)

struct B {
    static bool call(int a, float b, char c) {
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
        if constexpr (
            exz::static_member_function_call::exists<
                _T, // class type
                bool, // return type
                int, float, char // argument types
            >()
        ) {
            // call the static member function 
            // bool call(int, float, char)
            _T::call(5, 2.4f, 'A');
        }
    }
};

A<B, C> sA;
```


