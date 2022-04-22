[![Build Status](https://app.travis-ci.com/ThomasAUB/existenz.svg?branch=main)](https://travis-ci.com/ThomasAUB/existenz)



# Existenz


Single header file providing compile-time checks of existence of members.
Works with member functions, static members function, members and static members.


## Exemple

struct A {
  static bool isPositive(int i) { 
    return (i > 0);
  }
};


STATIC_MEMBER_FUNCTION(isPositive);

struct B {

  B(int i) {
  
    if constexpr( exz::static_member_function_isPositive::exists(A, bool, int) ) {
      
      if(A::isPositive(i)) {
        // ...
      }
      
    }
    
  }
}
