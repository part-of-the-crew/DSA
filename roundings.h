// -----------------------------------------------------------------------------
// 1. Macros
// -----------------------------------------------------------------------------
// Great for C or C++, but some C++ developers hate them since they may have the multiple evaluation
// problem where you pass in an expression as an input parameter and it gets evaluated multiple
// times.

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result UP (AWAY FROM ZERO) to the next whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, *add*
///             (abs(denom) - 1) to the numerator *prior to* the division, as this is the
///             equivalent of adding a *tiny bit less than 1* to the result, which will always
///             result in a rounding up once integer truncation takes place. Examples:
///             1/4 = 0.25, but we add (abs(denom) - 1) to the numerator --> (1 + (4 - 1))/4 =
///             (1 + 3)/4 = 4/4 = 1.
///             (2) when the division result will be negative, simply truncating the result by
///             performing division as normal results in a rounding-up effect.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded UP to the next *whole integer*!
#define DIVIDE_ROUND_AWAY_FROM_ZERO(numer, denom) DIVIDE_ROUNDUP((numer), (denom))
#define DIVIDE_ROUNDUP(numer, denom) (                                                  \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    (numer) / (denom) :                                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this, */    \
    /* acting slightly differently if denom is negative: */                             \
    ((numer) + ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom)                     \
)

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result DOWN (TOWARDS ZERO) to the next whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, simply truncating the result by
///             performing division as normal results in a rounding-down effect.
///             (2) When the division result will be negative, *subtract*
///             (abs(denom) - 1) from the numerator *prior to* the division, as this is the
///             equivalent of subtracting a *tiny bit less than 1* from the result, which will
///             always result in a rounding down once integer truncation takes place. Examples:
///             -1/4 = -0.25, but we subtract (abs(denom) - 1) from the numerator -->
///             (-1 - (4 - 1))/4 = (-1 - 3)/4 = -4/4 = -1.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded DOWN to the next *whole integer*!
#define DIVIDE_ROUND_TOWARDS_ZERO(numer, denom) DIVIDE_ROUNDDOWN((numer), (denom))
#define DIVIDE_ROUNDDOWN(numer, denom) (                                                \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this, */                        \
    /* acting slightly differently if denom is negative: */                             \
    ((numer) - ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom) :                   \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    (numer) / (denom)

/// @brief      A function-like macro to perform integer division of numer/denom, rounding the
///             result TO THE NEAREST whole integer.
/// @note       This works on *integers only* since it assumes integer truncation will take place
///             automatically during the division! It will NOT work properly on floating point
///             types! Valid types are int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
///             int64_t, uint64_t, etc.
/// @details    The concept is this:
///             (1) when the division result will be positive, *add* (denom/2) to
///             the numerator *prior to* the division, as this is the equivalent of adding
///             0.5 to the result, which will always result in rounding to the nearest whole
///             integer once integer truncation takes place. Examples:
///             3/4 = 0.75, but we add (denom/2) to the numerator --> (3 + 4/2)/4 =
///             (3 + 2)/4 = 5/4 = 1.25, which truncates to 1.
///             (2) when the division result will be negative, *subtract* (denom/2) from
///             the numerator *prior to* the division, as this is required to grow it by 0.5
///             in the direction *away from zero* (more negative in this case), which is required
///             for rounding to the nearest whole integer. The same principle as in the positive
///             case applies. Example: -3/4 = -0.75, but we subtract (denom/2) from the numerator
///             --> (-3 - 4/2)/4 = (-3 - 2)/4 = -5/4 = -1.25, which truncates to -1.
/// @param[in]  numer   The numerator in the division: any positive or negative integer
/// @param[in]  denom   The denominator in the division: any positive or negative integer
/// @return     The result of the (numer/denom) division rounded TO THE NEAREST *whole integer*!
#define DIVIDE_ROUNDNEAREST(numer, denom) (                                             \
    /* NB: `!=` acts as a logical XOR operator */                                       \
    /* See: https://stackoverflow.com/a/1596681/4561887 */                              \
    ((numer) < 0) != ((denom) < 0) ?                                                    \
    /* numer OR denom, but NOT both, is negative, so do this: */                        \
    ((numer) - ((denom)/2)) / (denom) :                                                 \
    /* numer AND denom are either *both positive* OR *both negative*, so do this: */    \
    ((numer) + ((denom)/2)) / (denom)                                                   \
)


// -----------------------------------------------------------------------------
// 2. Statement Expressions
// -----------------------------------------------------------------------------
// These solve the multiple evaluation problem of macros perfectly, but are not part of the C or
// C++ standard. Instead, they are gcc and clang compiler extensions to C and C++. These are safer
// to use than macros, but can still have a name pollution risk because variables created inside
// statement expressions are not in their own scope--rather, they are part of the outer scope.
// Nevertheless, prefer them to macros.

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUND_AWAY_FROM_ZERO2(numer, denom) DIVIDE_ROUNDUP2((numer), (denom))
#define DIVIDE_ROUNDUP2(numer, denom)                                           \
    ({                                                                          \
        __typeof__(numer) numer_ = (numer);                                     \
        __typeof__(denom) denom_ = (denom);                                     \
        ((numer_) < 0) != ((denom_) < 0) ?                                      \
            (numer_) / (denom_) :                                               \
            ((numer_) + ((denom_) < 0 ? (denom_) + 1 : (denom_)-1)) / (denom_); \
    })

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUND_TOWARDS_ZERO2(numer, denom) DIVIDE_ROUNDDOWN2((numer), (denom))
#define DIVIDE_ROUNDDOWN2(numer, denom)                                          \
    ({                                                                           \
        __typeof__(numer) numer_ = (numer);                                      \
        __typeof__(denom) denom_ = (denom);                                      \
        ((numer_) < 0) != ((denom_) < 0) ?                                       \
            ((numer_) - ((denom_) < 0 ? (denom_) + 1 : (denom_)-1)) / (denom_) : \
            (numer_) / (denom_);                                                 \
    })

/// @brief  *gcc statement expression* form of the above equivalent macro
#define DIVIDE_ROUNDNEAREST2(numer, denom)                                              \
({                                                                                      \
    __typeof__ (numer) numer_ = (numer);                                                \
    __typeof__ (denom) denom_ = (denom);                                                \
    ((numer_) < 0) != ((denom_) < 0) ?                                                  \
    ((numer_) - ((denom_)/2)) / (denom_) :                                              \
    ((numer_) + ((denom_)/2)) / (denom_);                                               \
})


// -----------------------------------------------------------------------------
// 3. C++ Templated Functions (AKA: Function Templates)
// -----------------------------------------------------------------------------
// Templates work in C++ only. They solve both problems above, and suffer neither from the multiple
// evaluation problem of macros, nor from the name pollution/variable scope problem of statement
// expressions. Since they work only in C++, I'm going to add type checking here too with a
// `static_assert()` using `std::numeric_limits`, but this feature could be *easily* added to both
// macros and statement expressions as well so long as you're using C++. Some C++ developers feel so
// strongly against macros (and are probably not aware of statement expressions) that they won't let
// you merge the above macro versions into their codebase. If this is the case, use templates.

#ifdef __cplusplus
#include <limits>

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_roundup(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        (numer) / (denom) :
        ((numer) + ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom);
    return result;
}

template <typename T>
inline T divide_round_away_from_zero(T numer, T denom)
{
    return divide_roundup(numer, denom);
}

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_rounddown(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        ((numer) - ((denom) < 0 ? (denom) + 1 : (denom) - 1)) / (denom) :
        (numer) / (denom);
    return result;
}

template <typename T>
inline T divide_round_towards_zero(T numer, T denom)
{
    return divide_rounddown(numer, denom);
}

/// @brief  C++ function template form of the above equivalent macro
template <typename T>
T divide_roundnearest(T numer, T denom)
{
    // Ensure only integer types are passed in, as this round division technique does NOT work on
    // floating point types since it assumes integer truncation will take place automatically
    // during the division!
    // - The following static assert allows all integer types, including their various `const`,
    //   `volatile`, and `const volatile` variations, but prohibits any floating point type
    //   such as `float`, `double`, and `long double`.
    // - Reference page: https://en.cppreference.com/w/cpp/types/numeric_limits/is_integer
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types are allowed");

    T result = ((numer) < 0) != ((denom) < 0) ?
        ((numer) - ((denom)/2)) / (denom) :
        ((numer) + ((denom)/2)) / (denom);
    return result;
}

#endif
