#pragma once
/**
 * Got it? 
 */

#include <string_view>

namespace type_writer
    {
    /**
     * stringified type_name output courtesy of Howard Hinnant
     * via: https://stackoverflow.com/a/56766138/7751352
     */
    template <typename T>
    constexpr std::string_view 
    type_name()
    {
        std::string_view name, prefix, suffix;
    #ifdef __clang__
        name = __PRETTY_FUNCTION__;
        prefix = "std::string_view typewriter::type_name() [T = ";
        suffix = "]";
    #elif defined(__GNUC__)
        name = __PRETTY_FUNCTION__;
        prefix = "constexpr std::string_view typewriter::type_name() [with T = ";
        suffix = "; std::string_view = std::basic_string_view<char>]";
    #elif defined(_MSC_VER)
        name = __FUNCSIG__;
        prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl typewriter::type_name<";
        suffix = ">(void)";
    #endif
        name.remove_prefix(prefix.size());
        name.remove_suffix(suffix.size());
        return name;
    }
}