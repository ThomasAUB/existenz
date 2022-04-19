#pragma once


//********************************************************************************/

#include <type_traits>


// OK
#define MEMBER_FUNCTION(function_name)                                              \
namespace exz {                                                                     \
class member_function_##function_name {                                             \
                                                                                    \
    template<typename ret_t, typename obj_t, typename... args_t>                    \
    static constexpr auto check(obj_t*)                                             \
    -> typename                                                                     \
        std::is_same<                                                               \
            decltype(                                                               \
                std::declval<obj_t>().function_name(std::declval<args_t>()...)),    \
                ret_t                                                               \
        >::type;                                                                    \
                                                                                    \
        template<typename...>                                                       \
        static constexpr std::false_type check(...);                                \
public:                                                                             \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \


// OK
#define STATIC_MEMBER_FUNCTION(function_name)                                       \
namespace exz {                                                                     \
class static_member_function_##function_name {                                      \
                                                                                    \
    template<typename ret_t, typename obj_t, typename... args_t>                    \
    static constexpr auto check(obj_t*)                                             \
    -> typename                                                                     \
        std::is_same<                                                               \
            decltype(                                                               \
                obj_t::function_name(std::declval<args_t>()...)),                   \
                ret_t                                                               \
        >::type;                                                                    \
                                                                                    \
    template<typename...>                                                           \
    static constexpr std::false_type check(...);                                    \
                                                                                    \
public:                                                                             \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \

/*
// NOK
#define FREE_FUNCTION(function_name)                                                \
namespace exz {                                                                     \
class free_function_##function_name {                                               \
                                                                                    \
    template<typename ret_t, typename... args_t>                                    \
    static constexpr auto check(ret_t(*)(args_t...) = &function_name)               \
    -> typename                                                                     \
        std::is_same<                                                               \
            decltype(function_name(std::declval<args_t>()...)), ret_t               \
        >::type;                                                                    \
                                                                                    \
    template<typename...>                                                           \
    static constexpr std::false_type check(...);                                    \
                                                                                    \
public:                                                                             \
    template<typename return_t = void, typename... args_t>                          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, args_t...>(0));                       \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \
*/

// OK
#define MEMBER(member_name)                                                         \
namespace exz {                                                                     \
class member_##member_name {                                                        \
                                                                                    \
    template<typename obj_t, typename member_t>                                     \
    static constexpr auto check(obj_t*)                                             \
    -> typename                                                                     \
        std::is_same<                                                               \
            decltype(                                                               \
                std::declval<obj_t>().member_name),                                 \
                member_t                                                            \
        >::type;                                                                    \
                                                                                    \
    template<typename...>                                                           \
    static constexpr std::false_type check(...);                                    \
                                                                                    \
public:                                                                             \
    template<typename obj_t, typename member_t>                                     \
    static constexpr bool exists() {                                                \
        using type = decltype(check<obj_t, member_t>(0));                           \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \








namespace exz_tests {

    MEMBER_FUNCTION(alala);

    STATIC_MEMBER_FUNCTION(hu);

    STATIC_MEMBER_FUNCTION(u);

    MEMBER(mMember);

    namespace A{

        struct Test1 {

            void alala() {}

            static bool hu(int) {return true;}

            float mMember;

            struct H{

                static void u(){}

            };
        };

        struct Test2 {

            struct H{};

        };

    }

    static_assert(exz::member_function_alala::exists<A::Test1>(), "EXISTENZ");
    static_assert(!exz::member_function_alala::exists<A::Test2>(), "EXISTENZ");

    static_assert(exz::static_member_function_hu::exists<A::Test1, bool, int>(), "EXISTENZ");
    static_assert(!exz::static_member_function_hu::exists<A::Test2, bool, int>(), "EXISTENZ");

    static_assert(exz::static_member_function_u::exists<A::Test1::H>(), "EXISTENZ");
    static_assert(!exz::static_member_function_u::exists<A::Test2::H>(), "EXISTENZ");

    static_assert(exz::member_mMember::exists<A::Test1, float>(), "EXISTENZ");
    static_assert(!exz::member_mMember::exists<A::Test2, float>(), "EXISTENZ");


}



///


