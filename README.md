[![Build Status](https://app.travis-ci.com/ThomasAUB/existenz.svg?branch=main)](https://travis-ci.com/ThomasAUB/existenz)



# Existenz


Single header file providing compile-time checks of existence of members.
Works with member functions, static member functions, members and static members.


## Exemple

```cpp

struct A {
  static bool isPositive(int i) { 
    return (i > 0);
  }
};



// declare existenz checking class
STATIC_MEMBER_FUNCTION(isPositive);



struct B {

  B(int i) {
  
    // if "bool A::isPositive)(int){}" exists
    if constexpr ( exz::static_member_function_isPositive::exists<A, bool, int>() ) { 
      
      if(A::isPositive(i)) {
        // ...
      }
      
    }
    
  }
};



// compile-time assert
static_assert( 
  exz::static_member_function_isPositive::exists<A, bool, int>(), 
  "bool A::isPositive)(int){} doesn't exist");


```
