#include "existenz.h"

// compile-time tests

MEMBER_FUNCTION(myMemberFunction);

STATIC_MEMBER_FUNCTION(myStaticMemberFunction);

MEMBER(myMember);

MEMBER(myStaticMember);

namespace A {

    struct Test {

        bool operator>(Test) {
            return false;
        }

        bool operator<(Test) {
            return false;
        }

        bool operator>=(Test) {
            return false;
        }

        bool operator<=(Test) {
            return false;
        }

        bool operator==(Test) {
            return false;
        }

        void operator()() {}

        void myMemberFunction() {}

        static bool myStaticMemberFunction(int) { return true; }

        float myMember;

        static inline bool myStaticMember = true;

    };

}

namespace B {

    struct Test {};

}


int main() {

    static_assert(exz::member_function_myMemberFunction::exists<A::Test>(), "EXISTENZ");

    static_assert(exz::member_function_myMemberFunction::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::member_function_myMemberFunction::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::static_member_function_myStaticMemberFunction::exists<A::Test, bool, int>(), "EXISTENZ");
    static_assert(!exz::static_member_function_myStaticMemberFunction::exists<B::Test, bool, int>(), "EXISTENZ");

    static_assert(exz::member_myMember::exists<A::Test, float>(), "EXISTENZ");
    static_assert(!exz::member_myMember::exists<B::Test, float>(), "EXISTENZ");

    static_assert(exz::member_myStaticMember::exists<A::Test, bool>(), "EXISTENZ");
    static_assert(!exz::member_myStaticMember::exists<B::Test, bool>(), "EXISTENZ");

    static_assert(exz::op::superior::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::superior::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::op::inferior::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::inferior::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::op::superior_equal::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::superior_equal::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::op::inferior_equal::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::inferior_equal::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::op::equal::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::equal::exists<B::Test>(), "EXISTENZ");

    static_assert(exz::op::parenthesis::exists<A::Test>(), "EXISTENZ");
    static_assert(!exz::op::parenthesis::exists<B::Test>(), "EXISTENZ");

}

