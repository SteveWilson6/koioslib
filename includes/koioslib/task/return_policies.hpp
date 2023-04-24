#ifndef KOIOS_TASK_RETURN_POLICIES
#define KOIOS_TASK_RETURN_POLICIES

#include <memory> // ::std::addressof
#include <utility>
#include <type_traits>

namespace wilson {

template<typename RetTraits>
requires (RetTraits::is_ref_v)
class return_policy {
private:
        using return_type = typename RetTraits::return_type;
        using store_type = typename RetTraits::store_type;

public:
        return_type get_value()(store_type t) const noexcept {
                return *t;
        }

        store_type set_value(return_type t) const noexcept {
                return ::std::addressof(t);
        }
};

template<typename RetTraits>
requires (not RetTraits::is_ref_v)
class return_policy {
private:
        using return_type = typename RetTraits::return_type;
        using store_type = typename RetTraits::store_type;

public:
        template<::std::same_as<store_type> T>
        return_type get_value()(store_type& t) const noexcept {
                return ::std::move(*t);
        }

        template<typename T>
        requires (::std::is_constructible_v<T, return_type>)
        store_type set_value(T&& t) {
                return store_type{ new return_type{ ::std::forward<T>(t) } };
        }
};

} // namespace wilson

#endif // KOIOS_TASK_RETURN_POLICIES
