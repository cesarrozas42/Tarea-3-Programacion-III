#include <iostream>
#include <vector>
#include <concepts>
#include <iterator>
#include <type_traits>
#include <numeric>
#include <algorithm>
#include <cstddef>

using namespace std;

namespace core_numeric {

    // 1. CONCEPTS OBLIGATORIOS Y PERSONALIZADOS

    // Concept: Iterable
    template <typename C>
    concept Iterable = requires(C c) {
        begin(c);
        end(c);
    };

    // Concept: Addable
    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> same_as<T>;
    };

    // Concept: Divisible
    template <typename T>
    concept Divisible = requires(T a, size_t n) {
        { a / n } -> same_as<T>;
    };

    // CONCEPT PERSONALIZADO: Comparable
    template <typename T>
    concept Comparable = requires(T a, T b) {
        { a > b } -> convertible_to<bool>;
        { a < b } -> convertible_to<bool>;
    };

    // ALGORITMOS SOBRE CONTENEDORES

    // Función sum (Reutilizada por mean)
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

    // 2. Algoritmo mean
    template <Iterable C>
        requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto mean(const C& container) {
        using T = typename C::value_type;
        T total = core_numeric::sum(container);
        size_t n = distance(begin(container), end(container));
        if (n == 0) return T{};
        return total / n;
    }

    // 3. Algoritmo variance
    template <Iterable C>
        requires Addable<typename C::value_type> && Divisible<typename C::value_type>
    auto variance(const C& container) {
        using T = typename C::value_type;
        T avg = core_numeric::mean(container);

        T sum_sq{};
        for (const auto& value : container) {
            T diff = value - avg;
            sum_sq = sum_sq + (diff * diff);
        }

        size_t n = distance(begin(container), end(container));
        if (n == 0) return T{};
        return sum_sq / n;
    }

    // 4. Algoritmo max
    template <Iterable C>
        requires Comparable<typename C::value_type>
    auto max(const C& container) {
        auto it = begin(container);
        auto max_val = *it;
        for (++it; it != end(container); ++it) {
            if (*it > max_val) {
                max_val = *it;
            }
        }
        return max_val;
    }

    // 5 Algoritmo transform_reduce
    template <Iterable C, typename F>
        requires Addable<invoke_result_t<F, typename C::value_type>>
    auto transform_reduce(const C& container, F function) {
        using T = invoke_result_t<F, typename C::value_type>;
        T result{};

        for (const auto& value : container) {
            result = result + function(value);
        }

        return result;
    }

    // 6 y 7. VARIADIC TEMPLATES, FOLD EXPRESSIONS & IF CONSTEXPR
    template <typename... Args>
        requires Addable<common_type_t<Args...>>
    auto sum_variadic(Args... args) {
        using T = common_type_t<Args...>;
        return (static_cast<T>(args) + ...);
    }

    template <typename... Args>
        requires Divisible<common_type_t<Args...>>
    auto mean_variadic(Args... args) {
        using T = common_type_t<Args...>;
        T sum = (static_cast<T>(args) + ...);
        return sum / sizeof...(args);
    }

    template <typename... Args>
        requires Addable<common_type_t<Args...>> && Divisible<common_type_t<Args...>>
    auto variance_variadic(Args... args) {
        using T = common_type_t<Args...>;
        T avg = mean_variadic(args...);

        T result = (((static_cast<T>(args) - avg) * (static_cast<T>(args) - avg)) + ...);

        return result / sizeof...(args);
    }

    template <typename T>
        requires Comparable<T>
    T max_two(T a, T b) {
        return a > b ? a : b;
    }

    template <typename T, typename... Args>
        requires Comparable<T>
    T max_variadic_impl(T first, Args... args) {
        T result = first;
        ((result = max_two(result, static_cast<T>(args))), ...);
        return result;
    }

    template <typename... Args>
        requires Comparable<common_type_t<Args...>>
    auto max_variadic(Args... args) {
        using T = common_type_t<Args...>;
        return max_variadic_impl<T>(static_cast<T>(args)...);
    }

    // 7. Ejemplo con if constexpr
    template <typename... Args>
        requires Addable<common_type_t<Args...>>
    auto sum_variadic_if_constexpr(Args... args) {
        using T = common_type_t<Args...>;

        if constexpr (is_integral_v<T>) {
            cout << "[Lógica para enteros detectada en compilación]" << endl;
            return (static_cast<T>(args) + ...);
        } else {
            cout << "[Lógica para flotantes detectada en compilación]" << endl;
            return (static_cast<T>(args) + ...);
        }
    }

} // namespace core_numeric

int main() {
    cout << "=== PRUEBAS CASOS VÁLIDOS (COMPILAN) ===" << endl;

    // Pruebas Contenedores
    vector<double> v{1.0, 2.0, 3.0};
    cout << "Mean: " << core_numeric::mean(v) << endl;                     // 2.0
    cout << "Variance: " << core_numeric::variance(v) << endl;             // 0.666667
    cout << "Max: " << core_numeric::max(v) << endl;                       // 3.0

    auto r = core_numeric::transform_reduce(v, [](double x) { return x * x; });
    cout << "Transform Reduce (x^2): " << r << endl;                       // 14.0

    // Pruebas Variádicas
    cout << "Sum Variadic: " << core_numeric::sum_variadic(1, 2, 3, 4) << endl;
    cout << "Mean Variadic: " << core_numeric::mean_variadic(0.1, 2.0, 3.0, 4.0) << endl;
    cout << "Variance Variadic: " << core_numeric::variance_variadic(1.0, 2.0, 3.0, 4.0) << endl;
    cout << "Max Variadic: " << core_numeric::max_variadic(1.0, 2.7, 3.0, 4.0) << endl;

    // Prueba if constexpr
    core_numeric::sum_variadic_if_constexpr(1, 2, 3);
    core_numeric::sum_variadic_if_constexpr(1.5, 2.5);

    return 0;
}