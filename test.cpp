#include <iostream>
#include <vector>
#include <string>

// Simulación de clase sin operador de división ni comparación
class Vector3D {
public:
    double x, y, z;
    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
};

int test() {

     //(Descomentar uno a uno para verificar los errores)

    // 1. FALLO DE CONCEPT: Divisible / Addable en std::string
    // std::vector<std::string> words{"Hola", "Mundo"};
    // auto v_err = core_numeric::variance(words);
    // ERROR: std::string no implementa división ni resta para la varianza.

    // 2. FALLO DE CONCEPT: Comparable
    // std::vector<Vector3D> vec_3d = {{1,2,3}, {4,5,6}};
    // auto max_val = core_numeric::max(vec_3d);
    // ERROR: Vector3D no satisface el concept Comparable (falta operator>).

    // 3. FALLO DE CONCEPT: Divisible
    // std::vector<Vector3D> vec_3d2 = {{1,2,3}, {4,5,6}};
    // auto m_val = core_numeric::mean(vec_3d2);
    // ERROR: Vector3D satisface Addable, pero falla en Divisible (falta operator/ por un std::size_t).

    // 4. FALLO DE CONCEPT: Iterable
    // int entero_simple = 10;
    // auto m_err = core_numeric::mean(entero_simple);
    // ERROR: 'int' no satisface el concept Iterable (no tiene std::begin / std::end).

    return 0;
}
