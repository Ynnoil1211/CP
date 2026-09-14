# 🎯 Búsqueda Binaria (Binary Search) en Competitive Programming

Guía completa y definitiva de Búsqueda Binaria en C++: desde los fundamentos de iteradores y cotas, hasta búsqueda sobre la respuesta (enteros y flotantes) y las trampas de rendimiento más letales de la STL.

---

## 📌 Tabla de Contenidos
1. [¿Por qué `left <= right`?](#1-por-qué-left--right)
2. [`lower_bound` vs `upper_bound` en Vectores](#2-lower_bound-vs-upper_bound-en-vectores)
3. [Las 4 Consultas Cardinales](#3-las-4-consultas-cardinales)
4. [⚠️ Trampa Mortal: `std::lower_bound` vs `container.lower_bound()`](#4-trampa-mortal-stdlower_bound-vs-containerlower_bound)
5. [Búsqueda Binaria sobre la Respuesta (Enteros)](#5-búsqueda-binaria-sobre-la-respuesta-enteros)
6. [Búsqueda Binaria sobre la Respuesta (Flotantes / Doubles)](#6-búsqueda-binaria-sobre-la-respuesta-flotantes--doubles)
7. [Checklist Rápido para Evitar Bugs](#7-checklist-rápido-para-evitar-bugs)

---

## 1. ¿Por qué `left <= right`?

En la búsqueda binaria clásica en un arreglo ordenado, el espacio de búsqueda se define con dos punteros: `left = 0` y `right = n - 1`.

En cada paso:
```cpp
mid = left + (right - left) / 2;
```
Y reducimos el espacio de forma **estricta**:
- Si descartamos la mitad derecha: `right = mid - 1`
- Si descartamos la mitad izquierda: `left = mid + 1`

### La razón del signo `=`
El signo `=` es **estrictamente necesario** porque **el elemento que buscas podría ser el último que queda** cuando `left` y `right` colapsan en el mismo índice (`left == right`).

> [!IMPORTANT]
> Si usaras `while (left < right)`, el ciclo terminaría inmediatamente cuando quede un solo elemento candidato en el rango, **sin evaluarlo jamás**. Al usar `<=`, ese último elemento se evalúa en `mid = left` y se toma la decisión correcta.

---

## 2. `lower_bound` vs `upper_bound` en Vectores

Ambas funciones asumen que el rango `[begin, end)` está **ordenado** de forma no descendente.

| Función | Definición Formal | Condición que busca | Al restar `begin()` |
|---|---|---|---|
| `lower_bound(..., X)` | Primer elemento ≥ X | `*it >= X` | Cantidad de elementos estrictamente menores que X (`< X`) |
| `upper_bound(..., X)` | Primer elemento > X | `*it > X` | Cantidad de elementos menores o iguales a X (`<= X`) |

### ¿Cuándo usar cuál?

#### Caso `upper_bound` (presupuesto / compras):
En [CF 706B - Interesting drink](https://codeforces.com/problemset/problem/706/B/), tienes monedas K y quieres saber en cuántas tiendas puedes comprar si el precio es ≤ K:
```cpp
// Precios: [1, 3, 6, 8, 9], Monedas: K = 8
auto it = upper_bound(prices.begin(), prices.end(), 8);
// it apunta a 9 (índice 4)
int tiendas = it - prices.begin(); // 4 tiendas (1, 3, 6, 8)
```

#### Caso `lower_bound` (presupuesto estricto):
Si la regla fuera *"Vasiliy solo compra si el refresco cuesta estrictamente menos que sus monedas (< K)"*:
```cpp
auto it = lower_bound(prices.begin(), prices.end(), 8);
// it apunta a 8 (índice 3)
int tiendas = it - prices.begin(); // 3 tiendas (1, 3, 6)
```

#### Frecuencia exacta de un elemento X:
```text
Frecuencia de X = upper_bound(X) - lower_bound(X)
```

```cpp
// Arreglo: [2, 4, 4, 4, 6] buscando el 4
auto low = lower_bound(v.begin(), v.end(), 4); // Apunta al primer 4 (índice 1)
auto up  = upper_bound(v.begin(), v.end(), 4); // Apunta al 6 (índice 4)
int count4 = up - low; // 4 - 1 = 3 repeticiones
```

---

## 3. Las 4 Consultas Cardinales

En problemas de CP con frecuencia necesitas una de las 4 consultas sobre un valor X. Con `lower_bound`, `upper_bound` y `prev()`, resuelves todas de forma segura:

```cpp
vector<int> a = {10, 20, 30, 40, 50};

// 1. Primer elemento >= X
auto it1 = lower_bound(a.begin(), a.end(), X);
if (it1 != a.end()) {
    cout << "Primero >= X es " << *it1 << "\n";
}

// 2. Primer elemento > X
auto it2 = upper_bound(a.begin(), a.end(), X);
if (it2 != a.end()) {
    cout << "Primero > X es " << *it2 << "\n";
}

// 3. Último elemento <= X (el mayor valor que no supera X)
auto it3 = upper_bound(a.begin(), a.end(), X);
if (it3 != a.begin()) {
    it3 = prev(it3); // o it3--
    cout << "Último <= X es " << *it3 << "\n";
} else {
    // Todos los elementos son > X (no existe ninguno <= X)
}

// 4. Último elemento < X (el mayor valor estrictamente menor que X)
auto it4 = lower_bound(a.begin(), a.end(), X);
if (it4 != a.begin()) {
    it4 = prev(it4); // o it4--
    cout << "Último < X es " << *it4 << "\n";
} else {
    // Todos los elementos son >= X (no existe ninguno < X)
}
```

> [!WARNING]
> Nunca uses `prev(it)` sin verificar previamente `it != a.begin()`. Si intentas retroceder el iterador que apunta a `begin()`, provocarás comportamiento indefinido (UB) o Crash (Segmentation Fault).

---

## 4. ⚠️ Trampa Mortal: `std::lower_bound` vs `container.lower_bound()`

Esta trampa ha causado incontables TLE (Time Limit Exceeded) en Codeforces y AtCoder:

```cpp
set<int> s;
multiset<int> ms;

// ❌ PÉSIMO (O(N) por consulta -> O(N^2) TLE total)
auto it = lower_bound(s.begin(), s.end(), X);
auto it = lower_bound(ms.begin(), ms.end(), X);

// ✅ CORRECTO (O(log N) por consulta -> O(N log N) total)
auto it = s.lower_bound(X);
auto it = ms.lower_bound(X);
```

### ¿Por qué pasa esto si el código compila?
- `vector` tiene iteradores de **acceso aleatorio** (`RandomAccessIterator`). `std::lower_bound` puede saltar directamente al elemento medio con `it + k` en O(1).
- `std::set` y `std::multiset` se implementan como árboles rojinegros (Red-Black Trees). Sus iteradores son **bidireccionales** (`BidirectionalIterator`), lo que significa que no pueden saltar en O(1); tienen que hacer `++it` nodo por nodo.
- Al llamar a `std::lower_bound(s.begin(), s.end(), X)`, la función STL no sabe cómo navegar el árbol; solo puede avanzar linealmente, tardando O(N).
- En cambio, el método miembro `s.lower_bound(X)` conoce la estructura del árbol y desciende directamente por la raíz y ramas en O(log N).

---

## 5. Búsqueda Binaria sobre la Respuesta (Enteros)

Se utiliza cuando la respuesta numérica X no es calculable directamente con una fórmula, pero **verificar si una propuesta X es válida toma tiempo polinomial (típicamente O(N))** mediante una función `check(X)`.

### Condición de Monotonicidad
El espacio de búsqueda debe tener una línea divisoria estricta (predicado monotónico):

- **Si buscas un mínimo:**
  ```text
  Valores insuficientes        Valores que cumplen
  [ Falso , Falso , Falso ] -> [ VERDADERO , Verdadero , Verdadero ]
                                  ^
                                  Queremos el primer Verdadero
  ```

- **Si buscas un máximo:**
  ```text
  Valores que cumplen              Valores excesivos
  [ Verdadero , Verdadero , VERDADERO ] -> [ Falso , Falso , Falso ]
                               ^
                               Queremos el último Verdadero
  ```

### Plantilla Universal Segura (con variable `ans`)
Esta plantilla elimina el dilema mental de si debes imprimir `left`, `right`, o `right + 1`:

```cpp
long long left = MIN_POSIBLE;
long long right = MAX_POSIBLE;
long long ans = -1; // Almacenará la mejor respuesta legal

while (left <= right) {
    long long mid = left + (right - left) / 2; // Seguro contra overflow
    
    if (check(mid)) {
        ans = mid; // ¡Funciona! Lo registramos
        
        // Si buscas el MÍNIMO: intentas mejorar buscando a la izquierda
        right = mid - 1;
        
        // Si buscas el MÁXIMO (descomentar si aplica):
        // left = mid + 1;
    } else {
        // No funcionó:
        // Si buscas el MÍNIMO, necesitas un valor más grande
        left = mid + 1;
        
        // Si buscas el MÁXIMO (descomentar si aplica):
        // right = mid - 1;
    }
}

cout << ans << "\n";
```

### Prevenir Overflow en `mid`:
```cpp
// ❌ Puede desbordar si left + right > 2^31 - 1
int mid = (left + right) / 2;

// ✅ Matemáticamente idéntico y 100% seguro contra overflow
long long mid = left + (right - left) / 2;
```

---

## 6. Búsqueda Binaria sobre la Respuesta (Flotantes / Doubles)

En problemas de geometría, física, promedios o ratios continuos, la respuesta es un número real (`double`).

### ¿Por qué NO usar `while (right - left > 1e-9)`?
- Los números de coma flotante tienen precisión finita (IEEE 754).
- Cerca de números grandes o por errores de redondeo, la diferencia `right - left` puede quedarse oscilando alrededor de `1e-9`, cayendo en un **ciclo infinito** o perdiendo precisión.

### La Técnica de Oro: 80 - 100 Iteraciones Fijas
Cada iteración divide el rango a la mitad. Con 100 iteraciones:
```text
Rango / (2^100) ≈ 10^9 / (1.26 × 10^30) ≈ 10^-21
```
Garantiza una precisión infinitamente superior a cualquier tolerancia requerida por un juez de CP (usualmente 10^-6 o 10^-9), sin riesgo de bucles infinitos.

```cpp
double left = 0.0, right = 1e9;

for (int iter = 0; iter < 100; iter++) {
    double mid = left + (right - left) / 2.0;
    
    if (check(mid)) {
        // Si buscamos el mínimo:
        right = mid;
        // Si buscamos el máximo: left = mid;
    } else {
        // Si buscamos el mínimo:
        left = mid;
        // Si buscamos el máximo: right = mid;
    }
}

// Al terminar, left y right son prácticamente idénticos
cout << fixed << setprecision(10) << left << "\n";
```

---

## 7. Checklist Rápido para Evitar Bugs

| Pregunta de Verificación | Acción Correcta |
|---|---|
| ¿El contenedor es `set` / `multiset`? | **Usa `s.lower_bound(x)`**, nunca `std::lower_bound` |
| ¿`left` y `right` pueden superar 10^9? | Usa `long long` para `left`, `right`, `mid` y límites |
| ¿Usas `prev(it)`? | Asegúrate primero de que `it != begin()` |
| ¿BS sobre doubles? | Haz un bucle fijo `for (int i = 0; i < 100; i++)` |
| ¿La función `check(mid)` es monotónica? | Dibuja en papel 3 valores de prueba para verificar FFFVVV o VVVFFF |