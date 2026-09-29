/**
 * ============================================================================
 * PLANTILLA: Geometría Computacional Básica 2D con Coordenadas Enteras
 * ARCHIVO:   cp-plantilla/geometry/geometria_basica.cpp
 * PARADIGMA: Computational Geometry / Vector Cross Product / Shoelace Formula
 * COMPLEJIDAD:
 *   - Producto cruz y orientación:        O(1) tiempo, O(1) espacio
 *   - Intersección de segmentos:           O(1) tiempo, O(1) espacio
 *   - Área de polígono (Shoelace area2):   O(N) tiempo, O(1) espacio
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Determinación de orientación relativa de puntos en 2D (giro a la izquierda,
 *    giro a la derecha, o puntos colineales).
 * 2. Algoritmos de envolvente convexa (Convex Hull: Graham Scan, Monotone Chain)
 *    donde se requiere verificar si un punto mantiene la curvatura CCW.
 * 3. Detección de intersección entre pares de segmentos de recta, incluyendo
 *    casos límite como segmentos colineales superpuestos, contactos en extremos y T-junctions.
 * 4. Cálculo del área exacta de polígonos simples (convexos o cóncavos) mediante la
 *    fórmula de Shoelace / Agrimensor sin sufrir imprecisiones de punto flotante.
 *
 * INVARIANTES CLAVE:
 * 1. Precisión entera absoluta (Zero Floating Point Issues):
 *    - Se emplean coordenadas enteras de 64 bits (long long).
 *    - Todas las decisiones de orientación e intersección se resuelven con sumas
 *      y multiplicaciones enteras, eliminando por completo errores de redondeo de double.
 * 2. Signo e interpretación del Producto Cruz:
 *    - cross(a, b, c) = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x).
 *    - cross(a, b, c) > 0: El punto c está a la izquierda de la recta dirigida ab (giro antihorario / CCW).
 *    - cross(a, b, c) < 0: El punto c está a la derecha de la recta dirigida ab (giro horario / CW).
 *    - cross(a, b, c) == 0: Los puntos a, b y c son colineales.
 * 3. Convenio de área 2 * Area (area2):
 *    - Retornar 2 * Area evita dividir por 2, conservando el valor como entero exacto.
 *    - Para obtener el área real: dividir por 2.0 solo al imprimir, o usar area2 / 2 y area2 % 2.
 * 4. Casos Borde en Intersección de Segmentos:
 *    - Si los extremos de ab están a lados opuestos de la recta soporte cd, y viceversa,
 *      la intersección es propia (en un punto interior).
 *    - Si el producto cruz es 0, se debe validar si el punto extremo está contenido
 *      en la caja delimitadora (bounding box) del otro segmento con on_segment.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

// Estructura fundamental de Punto en 2D con coordenadas enteras
struct Point {
    long long x, y;

    Point() : x(0), y(0) {}
    Point(long long _x, long long _y) : x(_x), y(_y) {}

    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Point& o) const { return !(*this == o); }
};

// Producto cruz 2D de dos vectores desde el origen: u.x * v.y - u.y * v.x
inline long long cross_product(Point u, Point v) {
    return u.x * v.y - u.y * v.x;
}

/**
 * Producto cruz orientado de los vectores (b - a) y (c - a).
 * Retorna:
 *   > 0 si c está a la izquierda del vector ab (giro antihorario / CCW)
 *   < 0 si c está a la derecha del vector ab (giro horario / CW)
 *   = 0 si a, b, c son colineales
 */
inline long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Producto punto (dot product): (b - a) . (c - a)
inline long long dot(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y);
}

/**
 * Doble del área de un polígono simple mediante la fórmula de Shoelace (Gauss).
 * Retorna 2 * Area como un entero exacto positivo.
 * Complejidad: O(N) tiempo, O(1) espacio auxiliar.
 */
long long area2(const std::vector<Point>& p) {
    int n = static_cast<int>(p.size());
    if (n < 3) return 0;
    long long res = 0;
    for (int i = 0; i < n; i++) {
        int next = (i + 1 == n ? 0 : i + 1);
        res += cross_product(p[i], p[next]);
    }
    return std::abs(res);
}

/**
 * Determina si el punto c se encuentra sobre el segmento cerrado ab.
 * Asume como precondición que a, b y c son colineales.
 */
inline bool on_segment(Point a, Point b, Point c) {
    return c.x >= std::min(a.x, b.x) && c.x <= std::max(a.x, b.x) &&
           c.y >= std::min(a.y, b.y) && c.y <= std::max(a.y, b.y);
}

// Función signo para evitar posibles desbordamientos de 64 bits en multiplicaciones
inline int sgn(long long val) {
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

/**
 * Determina si los segmentos cerrados ab y cd se intersectan en al menos un punto.
 * Maneja correctamente intersecciones propias, toques en extremos, T-junctions
 * y segmentos colineales superpuestos.
 * Complejidad: O(1) tiempo, O(1) espacio.
 */
bool segments_intersect(Point a, Point b, Point c, Point d) {
    int cp1 = sgn(cross(a, b, c));
    int cp2 = sgn(cross(a, b, d));
    int cp3 = sgn(cross(c, d, a));
    int cp4 = sgn(cross(c, d, b));

    // Caso general: los extremos de cada segmento yacen en lados opuestos de la recta soporte del otro
    if (cp1 * cp2 < 0 && cp3 * cp4 < 0) {
        return true;
    }

    // Casos particulares de colinealidad o puntos sobre segmentos
    if (cp1 == 0 && on_segment(a, b, c)) return true;
    if (cp2 == 0 && on_segment(a, b, d)) return true;
    if (cp3 == 0 && on_segment(c, d, a)) return true;
    if (cp4 == 0 && on_segment(c, d, b)) return true;

    return false;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== Demostracion: Geometria Basica 2D ===\n";

    // 1. Orientacion y producto cruz
    std::cout << "\n--- Orientacion y Producto Cruz ---\n";
    Point a(0, 0), b(4, 0);
    Point c1(2, 3);
    Point c2(2, -3);
    Point c3(8, 0);

    long long cp1 = cross(a, b, c1);
    long long cp2 = cross(a, b, c2);
    long long cp3 = cross(a, b, c3);

    std::cout << "Orientacion (0,0)->(4,0) con (2,3):  cross = " << cp1
              << (cp1 > 0 ? " (Giro antihorario / CCW)" : " (Giro horario / CW)") << "\n";
    std::cout << "Orientacion (0,0)->(4,0) con (2,-3): cross = " << cp2
              << (cp2 < 0 ? " (Giro horario / CW)" : " (Giro antihorario / CCW)") << "\n";
    std::cout << "Orientacion (0,0)->(4,0) con (8,0):  cross = " << cp3
              << " (Puntos colineales)\n";

    // 2. Area de poligonos (Formula de Shoelace)
    std::cout << "\n--- Formula de Shoelace (area2) ---\n";
    // Triangulo rectangulo base 4, altura 3 -> Area = 6
    std::vector<Point> triangle = {Point(0, 0), Point(4, 0), Point(0, 3)};
    long long t_area2 = area2(triangle);
    std::cout << "Triangulo (0,0), (4,0), (0,3):\n";
    std::cout << "  area2 = " << t_area2 << ", Area real = " << (t_area2 / 2.0) << "\n";

    // Cuadrado de lado 5 -> Area = 25
    std::vector<Point> square = {Point(0, 0), Point(5, 0), Point(5, 5), Point(0, 5)};
    long long sq_area2 = area2(square);
    std::cout << "Cuadrado de lado 5:\n";
    std::cout << "  area2 = " << sq_area2 << ", Area real = " << (sq_area2 / 2.0) << "\n";

    // Poligono no convexo en L -> Area = 12
    std::vector<Point> l_polygon = {
        Point(0, 0), Point(4, 0), Point(4, 2),
        Point(2, 2), Point(2, 4), Point(0, 4)
    };
    long long l_area2 = area2(l_polygon);
    std::cout << "Poligono en forma de L:\n";
    std::cout << "  area2 = " << l_area2 << ", Area real = " << (l_area2 / 2.0) << "\n";

    // 3. Interseccion de segmentos
    std::cout << "\n--- Interseccion de Segmentos ---\n";
    // Cruz interior (interseccion propia)
    Point p1(-2, 0), p2(2, 0), q1(0, -2), q2(0, 2);
    std::cout << "Cruz [-2,0]..[2,0] y [0,-2]..[0,2]:         "
              << (segments_intersect(p1, p2, q1, q2) ? "Intersectan" : "No intersectan") << "\n";

    // Comparten extremo
    Point r1(0, 0), r2(3, 3), r3(6, 0);
    std::cout << "Toque en vertice [0,0]..[3,3] y [3,3]..[6,0]: "
              << (segments_intersect(r1, r2, r2, r3) ? "Intersectan" : "No intersectan") << "\n";

    // Paralelos disjuntos
    Point s1(0, 0), s2(0, 4), s3(2, 0), s4(2, 4);
    std::cout << "Paralelos [0,0]..[0,4] y [2,0]..[2,4]:        "
              << (segments_intersect(s1, s2, s3, s4) ? "Intersectan" : "No intersectan") << "\n";

    // Colineales superpuestos
    Point t1(0, 0), t2(4, 0), t3(2, 0), t4(6, 0);
    std::cout << "Colineales superpuestos [0,0]..[4,0] y [2,0]..[6,0]: "
              << (segments_intersect(t1, t2, t3, t4) ? "Intersectan" : "No intersectan") << "\n";

    std::cout.flush();
    return 0;
}
