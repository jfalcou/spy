# SPY - C++17 preprocessor-less informations gathering

## Purpose
Detection and versioning of operating systems, compilers, architecture and other element are
traditionally done using preprocessor macros. Library like
[Boost.Predef](https://www.boost.org/doc/libs/release/doc/html/predef.html) provides a sanitized
interface on top of those but still live in a world where the preprocessor is king.

SPY is a C++17 (and onward) library that gathers similar informations and provides a `constexpr`
compatible interface to access those information, thus making their exploitation safe within the
now widely accepted `if constexpr` language construct.

## Basic usage

Let's write a function that call the appropriate version of `getenv` depending if we use Visual
Studio or not.

```cpp
std::string get_env(std::string const& name)
{
  if constexpr(spy::current_compiler_ == spy::compiler_::msvc_)
  {
    char* buf = 0;
    std::size_t sz = 0;

    _dupenv_s(&buf, &sz, name.c_str());

    std::string that = buf ? buf : " ";
    free(buf);

    return that;
  }
  else
  {
    auto p = std::getenv(name.c_str());
    std::string that = p ? p : "";
    return that;
  }
}
```

Instead of using preprocessor-guarded code fragment, we can use `if constexpr` directly.

In some case, we also need to be sure that your compiler is above a given version.

```cpp
std::pair<float,int>  foo(std::pair<int,float> const& x)
{
  // Structured bindings require Clang 4.x or greater
  if constexpr(     spy::current_compiler_ == spy::compiler_::clang_
                &&  spy::version_of(spy::current_compiler_) >= spy::version<4>
              )
  {
    auto [f,s] = x;
    return std::make_pair(s,f);
  }
  else
  {
    return std::make_pair(x.second,x.first);
  }
```

## Support

g++ | clang | MSVC | Intel
----|-------|------|------
7   |3.9    |15.5.*|19.0

## Useful Links
