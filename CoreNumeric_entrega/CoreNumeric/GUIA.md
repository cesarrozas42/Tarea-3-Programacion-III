# CoreNumeric - guía de entrega

## Estructura

- `include/core_numeric.hpp`: implementación completa de la librería.
- `tests/test_sum.cpp`: pruebas de `sum`.
- `tests/test_mean.cpp`: pruebas de `mean`.
- `tests/test_variance.cpp`: pruebas de `variance`.
- `tests/test_max.cpp`: pruebas de `max`.
- `tests/test_transform_reduce.cpp`: pruebas de `transform_reduce`.
- `tests/test_variadic.cpp`: pruebas de variadic templates y fold expressions.
- `tests/test_if_constexpr.cpp`: demostración de `if constexpr`.
- `CMakeLists.txt`: compilación con C++20.
- `README.md`: contiene únicamente el nombre del estudiante, como exige el enunciado.

## Compilar con CMake

```bash
cmake -S . -B build
cmake --build build
```

Luego se pueden ejecutar los programas generados:

```bash
./build/test_sum
./build/test_mean
./build/test_variance
./build/test_max
./build/test_transform_reduce
./build/test_variadic
./build/test_if_constexpr
```

En Windows con Visual Studio, los ejecutables pueden quedar dentro de `build/Debug/`.

## Decisiones

- `Iterable`, `Addable` y `Divisible` siguen la forma indicada en el enunciado.
- `Comparable` es el concept adicional creado para restringir `max`.
- `variance` usa la varianza poblacional: suma de `(x - media)^2` dividida entre `n`.
- Los casos que deben NO compilar están comentados dentro de cada test para que los archivos puedan compilar normalmente. Se explica junto a cada caso qué concept falla.
- `transform_reduce` recibe la operación como parámetro de tipo `F`.
- Las funciones variádicas utilizan fold expressions.
- `if constexpr` aparece en `normalize`, diferenciando tipos integrales y flotantes sin lógica de ejecución.
