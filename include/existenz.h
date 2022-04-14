#pragma once


//********************************************************************************/

#include <type_traits>

namespace exz {

    struct exz_base {
    protected:
        template<typename...>
        static constexpr std::false_type check(...);
    };

}


// OK
#define MEMBER_FUNCTION(function_name)                                              \
namespace exz {                                                                     \
class member_function_##function_name : exz_base {                                  \
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
public:                                                                             \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}


// OK
#define STATIC_MEMBER_FUNCTION(function_name)                                       \
namespace exz {                                                                     \
class static_member_function_##function_name : exz_base {                           \
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
public:                                                                             \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}


// NOK
#define FREE_FUNCTION(function_name)                                                \
namespace exz {                                                                     \
class free_function_##function_name : exz_base {                                    \
                                                                                    \
    template<typename ret_t, typename... args_t>                                    \
    static constexpr auto check(ret_t(*)(args_t...))                                \
    -> typename                                                                     \
        std::is_same<                                                               \
            decltype(function_name(std::declval<args_t>()...)), ret_t               \
        >::type;                                                                    \
                                                                                    \
public:                                                                             \
    template<typename return_t = void, typename... args_t>                          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, args_t...>(0));                       \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}


// OK
#define MEMBER(member_name)                                                         \
namespace exz {                                                                     \
class member_##member_name : exz_base {                                             \
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
public:                                                                             \
    template<typename obj_t, typename member_t>                                     \
    static constexpr bool exists() {                                                \
        using type = decltype(check<obj_t, member_t>(0));                           \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}





