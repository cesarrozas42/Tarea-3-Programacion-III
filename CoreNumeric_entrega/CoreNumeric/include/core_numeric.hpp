#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

namespace core_numeric {

// ============================================================
// Concepts obligatorios
// ============================================================

template <typename C>
concept Iterable = requires(C c) {
    std::begin(c);
    std::end(c);
};

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <typename T>
concept Divisible = requires(T a, std::size_t n) {
    { a / n } -> std::same_as<T>;
};

// Concept propio: permite determinar si dos objetos pueden ordenarse.
// Se utiliza en max().
template <typename T>
concept Comparable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

// Restricciones auxiliares para variance.
template <typename T>
concept VarianceElement = requires(T a, T b) {
    { a - b };
    { a * b };
};

template <Iterable C>
requires Addable<typename C::value_type>
auto sum(const C& container) {
    using T = typename C::value_type;

    T result{};

    for (const auto& value : container) {
        result = result + value;
    }

    return result;
}

template <Iterable C>
requires Divisible<typename C::value_type> &&
         Addable<typename C::value_type>
auto mean(const C& container) {
    const auto n = static_cast<std::size_t>(
        std::distance(std::begin(container), std::end(container))
    );

    return sum(container) / n;
}

template <Iterable C>
requires Addable<typename C::value_type> &&
         Divisible<typename C::value_type> &&
         VarianceElement<typename C::value_type>
auto variance(const C& container) {
    using T = typename C::value_type;

    const auto n = static_cast<std::size_t>(
        std::distance(std::begin(container), std::end(container))
    );

    if (n == 0) {
        return T{};
    }

    const T average = mean(container);
    T result{};

    for (const auto& value : container) {
        const T difference = value - average;
        result = result + difference * difference;
    }

    return result / n;
}

template <Iterable C>
requires Comparable<typename C::value_type>
auto max(const C& container) {
    using T = typename C::value_type;

    auto it = std::begin(container);
    const auto last = std::end(container);

    if (it == last) {
        return T{};
    }

    T result = *it;
    ++it;

    for (; it != last; ++it) {
        if (result < *it) {
            result = *it;
        }
    }

    return result;
}

// La función recibida se maneja como parámetro template mediante el tipo F.
template <Iterable C, typename F>
requires std::invocable<F, typename C::value_type>
auto transform_reduce(const C& container, F function) {
    using Result = std::invoke_result_t<F, typename C::value_type>;

    Result result{};

    for (const auto& value : container) {
        result = result + std::invoke(function, value);
    }

    return result;
}

// ============================================================
// Variadic templates + fold expressions
// ============================================================

template <typename... Args>
requires (sizeof...(Args) > 0) &&
         requires(Args... args) {
             (args + ...);
         }
auto sum_variadic(Args... args) {
    return (args + ...);
}

template <typename... Args>
requires (sizeof...(Args) > 0)
auto mean_variadic(Args... args) {
    using Common = std::common_type_t<Args...>;

    const Common total = (static_cast<Common>(args) + ...);
    constexpr std::size_t n = sizeof...(Args);

    return total / static_cast<Common>(n);
}

template <typename... Args>
requires (sizeof...(Args) > 0)
auto variance_variadic(Args... args) {
    using Common = std::common_type_t<Args...>;

    const Common average = mean_variadic(args...);

    Common result{};
    ((result = result +
        (static_cast<Common>(args) - average) *
        (static_cast<Common>(args) - average)), ...);

    constexpr std::size_t n = sizeof...(Args);
    return result / static_cast<Common>(n);
}

template <typename T, typename... Rest>
requires (std::same_as<T, Rest> && ...) &&
         Comparable<T>
auto max_variadic(T first, Rest... rest) {
    T result = first;

    ((result = (result < rest ? rest : result)), ...);

    return result;
}

// ============================================================
// Uso obligatorio de if constexpr
// ============================================================

template <typename T>
requires std::is_arithmetic_v<T>
constexpr T normalize(T value) {
    if constexpr (std::is_integral_v<T>) {
        // Para enteros se conserva el valor como entero.
        return value;
    } else {
        // Para flotantes se convierte explícitamente a la forma flotante.
        return static_cast<T>(value);
    }
}

} // namespace core_numeric
