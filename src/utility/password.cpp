#include "koioslib/utility/password.hpp"
#include <algorithm>
#include <cstring>

namespace wilson {

password::password(::std::string_view s)
        : size_{ s.size() + 1 }, stor_{ new char[size_]{} }
{
        char* stor_pointer = stor_.get();
        ::std::copy(s.begin(), s.end(), stor_pointer);
}

void password::complete_erase() noexcept {
        ::memset(stor_.get(), 0, size_); // TODO maybe UB
}

password::~password() {
        complete_erase();
}

::std::string_view password::get() const noexcept {
        return { stor_.get(), size_ - 1 }; // TODO need test
}

}
