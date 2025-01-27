/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                     *
 *                                                                                 *
 * Copyright (c) 2022 Thomas AUBERT                                                *
 *                                                                                 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy    *
 * of this software and associated documentation files (the "Software"), to deal   *
 * in the Software without restriction, including without limitation the rights    *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is           *
 * furnished to do so, subject to the following conditions:                        *
 *                                                                                 *
 * The above copyright notice and this permission notice shall be included in all  *
 * copies or substantial portions of the Software.                                 *
 *                                                                                 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 * SOFTWARE.                                                                       *
 *                                                                                 *
 * github : https://github.com/ThomasAUB/Existenz                                  *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once


#include <type_traits>


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
    template<typename...>                                                           \
    static constexpr std::false_type check(...);                                    \
                                                                                    \
public:                                                                             \
                                                                                    \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \


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
                                                                                    \
    template<typename obj_t, typename return_t = void, typename... args_t>          \
    static constexpr bool exists() {                                                \
        using type = decltype(check<return_t, obj_t, args_t...>(0));                \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \


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
                                                                                    \
    template<typename obj_t, typename member_t>                                     \
    static constexpr bool exists() {                                                \
        using type = decltype(check<obj_t, member_t>(0));                           \
        return type::value;                                                         \
    }                                                                               \
};                                                                                  \
}                                                                                   \



#define TYPE(type_name, real_type)                                \
    namespace exz {                                               \
    class type_##type_name {                                      \
        template <typename T, typename = void>                    \
        struct type_exists : std::false_type {};                  \
                                                                  \
        template <typename T>                                     \
        struct type_exists<T, std::void_t<typename T::real_type>> \
            : std::true_type {};                                  \
                                                                  \
       public:                                                    \
        template <typename input_t>                               \
        static constexpr bool exists() {                          \
            return type_exists<input_t>::value;                   \
        }                                                         \
    };                                                            \
}




namespace exz::op {
class parenthesis {

    template<typename ret_t, typename obj_t, typename... args_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                std::declval<obj_t>()(std::declval<args_t>()...)),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = void, typename... args_t>
    static constexpr bool exists() {
        using type = decltype(check<return_t, obj_t, args_t...>(0));
        return type::value;
    }
};
}

namespace exz::op {
class inferior {

    template<typename obj_t, typename ret_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                (std::declval<obj_t>() < std::declval<obj_t>())),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = bool>
    static constexpr bool exists() {
        using type = decltype(check<obj_t, return_t>(0));
        return type::value;
    }
};
}

namespace exz::op {
class superior {

    template<typename obj_t, typename ret_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                (std::declval<obj_t>() > std::declval<obj_t>())),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = bool>
    static constexpr bool exists() {
        using type = decltype(check<obj_t, return_t>(0));
        return type::value;
    }
};
}

namespace exz::op {
class superior_equal {

    template<typename obj_t, typename ret_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                (std::declval<obj_t>() >= std::declval<obj_t>())),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = bool>
    static constexpr bool exists() {
        using type = decltype(check<obj_t, return_t>(0));
        return type::value;
    }
};
}

namespace exz::op {
class inferior_equal {

    template<typename obj_t, typename ret_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                (std::declval<obj_t>() <= std::declval<obj_t>())),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = bool>
    static constexpr bool exists() {
        using type = decltype(check<obj_t, return_t>(0));
        return type::value;
    }
};
}

namespace exz::op {
class equal {

    template<typename obj_t, typename ret_t>
    static constexpr auto check(obj_t*)
    -> typename
        std::is_same<
            decltype(
                (std::declval<obj_t>() == std::declval<obj_t>())),
                ret_t
        >::type;

    template<typename...>
    static constexpr std::false_type check(...);

public:

    template<typename obj_t, typename return_t = bool>
    static constexpr bool exists() {
        using type = decltype(check<obj_t, return_t>(0));
        return type::value;
    }
};
}
