# RPC 08 (Septiembre 2026) / NAQ 2023-2024 — Reporte Maestro y Editorial de Estudio

Bienvenido al repositorio de análisis técnico, notas de estudio y catalogación de antipatrones de la **8ª Actividad de la Red de Programación Competitiva (RPC 08 - Septiembre 2026)**, correspondiente al conjunto oficial del **North America Qualifier (NAQ 2023-2024)**.

Este documento consolida la autopsia técnica de los envíos del equipo, la comparativa contra las soluciones oficiales de Arup Guha, y la hoja de ruta pedagógica para el upsolving del set completo.

---

## 1. Cuadro de Honor y Métricas del Problemset

| ID | Problema | Estado en Concurso | Versión AC | Dificultad | Paradigma / Algoritmo Principal | Complejidad Temporal |
| :---: | :--- | :---: | :---: | :---: | :--- | :---: |
| **A** | [Contest Advancement](outputs/notes/A_Contest_Advancement.md) | **AC** | Versión 3 | Div 2A | Filtro Greedy en 2 Pases + Hash Set | `O(N log N)` |
| **B** | [Digit Translation](outputs/notes/B_Digit_Translation.md) | *Upsolved* | Oficial | Div 2C / Div 1A | Programación Dinámica Lineal 1D (Min + Conteo) | `O(N)` |
| **C** | [Don't Hunger Together](outputs/notes/C_Dont_Hunger_Together.md) | *Upsolved* | Oficial | Div 1B / Div 2E | Búsqueda Binaria sobre la Respuesta + Min-Heap (EDF) | `O(I * N log N)` |
| **D** | [Garden of Thorns](outputs/notes/D_Garden_of_Thorns.md) | *Upsolved* | Oficial | Div 1C / Div 2F | Linealidad de la Esperanza + Geometría Círculo-Caja | `O(N)` |
| **E** | [ICPC Team Generation](outputs/notes/E_ICPC_Team_Generation.md) | **AC** | Versión 1 | Div 2B | Barrido Greedy Monótono (Monotonic Sliding) | `O(N)` |
| **F** | [Is Y a Vowel?](outputs/notes/F_Is_Y_a_Vowel.md) | **AC** | Versión 1 | Div 3A | Simulación Lineal de Cadenas | `O(|S|)` |
| **G** | [Lines Per Hour](outputs/notes/G_Lines_Per_Hour.md) | **AC** | Versión 2 | Div 3A | Ordenamiento Codicioso (Greedy Knapsack Fractional) | `O(N log N)` |
| **H** | [Magnesium Supplementation](outputs/notes/H_Magnesium_Supplementation.md) | **AC** | Versión 3 | Div 2B | Teoría de Números (Factorización `O(sqrt(N))`) | `O(sqrt(N) + D log D)` |
| **I** | [Missing Number](outputs/notes/I_Missing_Number.md) | *Upsolved* | Oficial | Div 2C | Fuerza Bruta sobre Prefijo (`L <= 5`) + Simulación | `O(sum |S|)` |
| **J** | [Tip of Your Tongue](outputs/notes/J_Tip_of_Your_Tongue.md) | *Upsolved* | Oficial | Div 1B / Div 2E | Doble Hashing Polinomial + Tablas Hash + PIE | `O(sum |W| + sum |p|)` |
| **K** | [Very Important Edge](outputs/notes/K_Very_Important_Edge.md) | *Upsolved* | Oficial | Div 1C | Kruskal MST + Path Min Range Update con DSU | `O(M log M)` |
| **L** | [Water Journal](outputs/notes/L_Water_Journal.md) | **AC** | Versión 2 | Div 3A | Análisis de Casos Borde + Principio del Palomar | `O(N)` |

- **Resueltos durante el concurso:** 6 / 12 (50% de efectividad).
- **Problemas resueltos en primer intento (AC directo):** 2 (E, F).
- **Problemas que requirieron depuración iterativa:** 4 (A, G, H, L).
- **Problemas pendientes para consolidación técnica:** 6 (B, C, D, I, J, K).

---

## 2. Catálogo de Errores y Antipatrones en Concurso

A partir del análisis diferencial de las versiones previas en `inputs/solutions/`, se identifican los siguientes sesgos y fallos críticos:

### 2.1. El "Síndrome del Ejemplo Quemado" (Problema G)
- **Manifestación:** En `Lines.cpp`, el código incluía `if (sum > 500) return i;`. El número `500` provenía del primer caso de ejemplo donde 5 horas * 100 líneas/hora = 500.
- **Causa Raíz:** Codificar directamente el cálculo mental realizado al leer el enunciado de muestra en lugar de la variable de entrada `5 * b`.
- **Prevención:** Jamás escribir números mágicos derivados de los ejemplos en condiciones de corte. Usar siempre nombres de variables descriptivos o constantes calculadas desde el input.

### 2.2. Fall-Through y Ausencia de Retorno por Defecto (Problema G)
- **Manifestación:** En `Lines (1).cpp`, la función iteraba buscando el momento en que se superaba el tiempo. Si la suma de todos los problemas era menor o igual a la capacidad, el bucle terminaba sin ejecutar ningún `return`. En C++, esto produce comportamiento indefinido (*Undefined Behavior*), retornando valores basura de memoria.
- **Prevención:** Toda función de búsqueda con retorno anticipado debe tener una sentencia `return` final que atienda el caso en que la condición de corte nunca se activa (ej. `return n;`).

### 2.3. Desbordamiento Silencioso por Typedef Inconsistente (Problema H)
- **Manifestación:** En `Magnesium (2).cpp`, las variables se leían como `ll n, y, z;` (hasta `10^12`), pero el contenedor de almacenamiento era `vi vt;` (`vector<int>`, donde `int` soporta hasta `2 * 10^9`). Al almacenar los divisores conjugados `N/i <= 10^12`, ocurrieron desbordamientos negativos inmediatos.
- **Causa Raíz:** Usar macros de plantillas prefabricadas por inercia (`vi` en lugar de `vll`).
- **Prevención:** Mantener coherencia absoluta en la cadena de tipos: si la entrada requiere 64 bits, todos los vectores, funciones auxiliares y acumuladores asociados deben ser estrictamente de 64 bits.

### 2.4. Confusión entre Espacio de Búsqueda y Magnitud de Entrada (Problema H)
- **Manifestación:** Los intentos iniciales en Python iteraban `range(1, k+1)` con `K <= 10^12`, produciendo TLE fulminante.
- **Causa Raíz:** Fijarse en la cota de la pastilla (`K`) en lugar de explotar la propiedad estructural de divisibilidad de `N`, que solo requiere explorar hasta `sqrt(N) <= 10^6`.
- **Prevención:** Antes de iterar sobre una variable acotada por `10^12`, verificar si existe una relación matemática dual que permita mapear el problema a `O(sqrt(N))` o `O(log N)`.

### 2.5. Impresión Codiciosa Fuera de Orden Relativo (Problema A)
- **Manifestación:** En `Contest (1).cpp`, los equipos clasificados en la primera fase se imprimían en caliente. Cuando se ejecutó la segunda fase de relleno, los clasificados del desempate salieron al final del archivo, violando la regla de "imprimir en orden de mérito original".
- **Causa Raíz:** Mezclar la fase de decisión/filtrado con la fase de presentación de salida.
- **Prevención:** En problemas con reglas de clasificación compuestas en múltiples pasadas, almacenar las decisiones en un conjunto o bandera booleana y realizar una pasada final de impresión sobre el orden canónico requerido.

### 2.6. La Falacia de la Condición Complementaria (Problema L)
- **Manifestación:** En `Water.cpp`, el código estructuraba `if (tiene_min) ... else cout << a;`. Se asumía erróneamente que si faltaba el mínimo, el máximo debía estar presente obligatoriamente. Se omitió el caso donde **ambos** estaban ausentes en el registro con `a != b`, situación en la cual es imposible cubrir ambos con un solo día restante (debía responder `-1`).
- **Causa Raíz:** Tratar dos condiciones booleanas independientes como si fueran mutuamente excluyentes y exhaustivas.
- **Prevención:** Elaborar una tabla de verdad exhaustiva (2^k estados) cuando se manejen múltiples restricciones de frontera.

---

## 3. Síntesis de Técnicas Avanzadas del Problemset (Guía de Upsolving)

### A. Programación Dinámica Lineal Simultánea (Problema B)
- **Patrón:** Procesar cadenas donde las transiciones abarcan ventanas cortas (`L en [3, 5]`).
- **Lección:** Mantener dos arreglos paralelos: uno para la optimización (`dp_len[i]`) y otro para la combinatoria módulo `M` (`dp_cnt[i]`). Cuando se encuentra un costo menor, el conteo se reinicia; cuando se empata el costo óptimo, los conteos se suman.

### B. BSTA + Min-Heap Greedy con Fechas Límite (Problema C)
- **Patrón:** Búsqueda binaria continua para optimizar una tasa de consumo diario, combinada con la estrategia de planificación de tareas *Earliest Deadline First* (EDF).
- **Lección:** El recurso más perecedero debe consumirse siempre antes que los recursos con fecha lejana. La cola de prioridad permite simular el consumo exacto en `O(N log N)` por iteración.

### C. Linealidad de la Esperanza en Geometría (Problema D)
- **Patrón:** Cálculo de valores esperados de múltiples objetos aleatoriamente afectados por una forma geométrica.
- **Lección:** Descomponer la esperanza total en la suma de probabilidades individuales `E[sum V_i] = sum V_i * P(E_i)`, transformando el problema en el cálculo del área de corte entre un círculo y un rectángulo alineado.

### D. Parsing Exhaustivo Acotado por Cota Superior (Problema I)
- **Patrón:** Secuencia numérica oculta concatenada donde falta un elemento.
- **Lección:** Cuando la cota del valor inicial es pequeña (`A <= 99999`), el número de dígitos iniciales está acotado por 5. Probar cada longitud inicial convierte todo el resto del problema en una verificación determinista sin bifurcaciones.

### E. Doble Hashing Polinomial + Principio de Inclusión-Exclusión (Problema J)
- **Patrón:** Consultas sobre prefijos y sufijos de igual longitud con operadores lógicos (`AND`, `OR`, `XOR`).
- **Lección:** Todo operador lógico de conjuntos sobre dos eventos se reduce a calcular `|A|`, `|B|` y `|A ∩ B|`. Con doble hash polinomial, estas tres cantidades se indexan en `O(1)` por longitud de patrón.

### F. DSU Path Compression en Árboles / 2nd Best MST (Problema K)
- **Patrón:** Determinar el impacto en el MST tras la eliminación de cada arista individual.
- **Lección:** Una arista fuera del árbol `e' = (u, v)` puede sustituir a cualquier arista de árbol en el camino entre `u` y `v`. Ordenar las aristas de reemplazo por peso permite pintar el árbol de abajo hacia arriba en tiempo casi lineal amortizado usando DSU.

---

## 4. Estructura de Archivos del Repositorio

```text
rpc_08_2026/
├── README.md                              # Reporte maestro y editorial de estudio
├── inputs/
│   ├── problemset/
│   │   └── ProblemsetRPC08.pdf            # PDF oficial del concurso
│   ├── solutions/                         # Soluciones aceptadas (AC) del equipo
│   │   ├── A_Contest.cpp
│   │   ├── E_Team.cpp
│   │   ├── F_Vowel.cpp
│   │   ├── G_Lines.cpp
│   │   ├── H_Magnesium.cpp
│   │   └── L_Water.cpp
│   └── official_solutions/               # Códigos de referencia oficiales (Arup Guha)
│       ├── A_Contest.cpp
│       ├── B_DigitTranslation.java
│       ├── C_Hunger.cpp
│       ├── D_Garden.java
│       ├── E_Team.cpp
│       ├── F_Vowel.cpp
│       ├── G_Lines.py
│       ├── H_Magnesium.py
│       ├── I_Missing.cpp
│       ├── J_Tongue.java
│       └── L_Water.py
└── outputs/
    └── notes/                             # 12 notas de estudio técnicas individuales
        ├── A_Contest_Advancement.md
        ├── B_Digit_Translation.md
        ├── C_Dont_Hunger_Together.md
        ├── D_Garden_of_Thorns.md
        ├── E_ICPC_Team_Generation.md
        ├── F_Is_Y_a_Vowel.md
        ├── G_Lines_Per_Hour.md
        ├── H_Magnesium_Supplementation.md
        ├── I_Missing_Number.md
        ├── J_Tip_of_Your_Tongue.md
        ├── K_Very_Important_Edge.md
        └── L_Water_Journal.md
```
