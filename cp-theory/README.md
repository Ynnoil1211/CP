# 📚 CP Theory & Cheatsheets

Repositorio de notas teóricas, guías de referencia rápida y plantillas para Competitive Programming en C++.

---

## 📑 Módulos Disponibles

### 1. [🎯 Búsqueda Binaria (Binary Search)](./binary-search/README.md)
Guía exhaustiva para dominar la búsqueda binaria y evitar trampas de complejidad:
- **Fundamentos:** ¿Por qué `left <= right`?, cotas semiabiertas vs cerradas.
- **`lower_bound` vs `upper_bound`:** Definiciones formales y ejemplos con problemas clásicos (CF 706B).
- **Las 4 Consultas Cardinales:** Cómo hallar de forma segura:
  1. Primer $\ge X$
  2. Primer $> X$
  3. Último $\le X$ (`prev`)
  4. Último $< X$ (`prev`)
- **⚠️ La Trampa Mortal:** Por qué `std::lower_bound` en `std::set` / `std::multiset` toma $O(N)$ y cómo `container.lower_bound()` lo resuelve en $O(\log N)$.
- **BS on Answer (Enteros):** Plantilla a prueba de fallos con variable `ans` y prevención de overflow en `mid`.
- **BS on Answer (Doubles):** Por qué no usar `while (r - l > eps)` y la técnica de las 80-100 iteraciones fijas.

---

### 2. [📦 Estructuras de Datos de la STL](./data-structures/README.md)
Referencia completa de contenedores asociativos y ordenados:
- **`std::set`:** Elementos únicos ordenados, búsqueda binaria interna, obtención de mínimo y máximo en $O(1)$.
- **`std::multiset`:** Duplicados ordenados.
  - ⚠️ **Trampa #1:** `ms.erase(val)` (borra todo) vs `ms.erase(it)` (borra una sola copia).
  - ⚠️ **Trampa #2:** Por qué `ms.count(val)` no es $O(\log N)$ y cómo usar `ms.find()`.
- **`std::map`:** Pares clave-valor ordenados, búsqueda por clave y el peligro de inserción implícita de `operator[]`.
- **`std::unordered_set` y `std::unordered_map`:** Tablas hash $O(1)$, prevención de ataques de colisión en Codeforces con `custom_hash` (SplitMix64).
- **Comparadores Personalizados (`Custom Comparators`):** Sets descendentes (`greater<int>`), structs personalizadas y orden estricto débil.
- **Diagrama de Decisión y Tabla Comparativa:** Cuándo elegir cada estructura.
