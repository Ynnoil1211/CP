# 💡 CP Insights — Biblioteca de Tarjetas de Patrones (Pattern Flashcards)

Repositorio de **tarjetas de estudio de alta densidad conceptual** para Competitive Programming (Codeforces, ICPC, RPC, AtCoder).

Cada tarjeta condensa el "momento eureka" (*aha moment*), la invariante matemática fundamental, las pistas en los límites (*pattern triggers*) y un fragmento de código esencial (*code spotlight*) de 3 a 8 líneas.

---

## 🎯 Filosofía y Organización

- **Eje Principal:** Clasificación rigurosa por **patrón algorítmico y subtipo** (`[paradigma]-[subtipo]`), no por fecha ni plataforma.
- **Formato Estricto:** Markdown limpio, 100% libre de sintaxis LaTeX cruda (notación con comillas simples y código: `O(N)`, `sqrt(N)`, `1 <= K <= 10^5`).
- **Propósito:** Repaso acelerado pre-competencia para detonar reconocimiento de patrones en tiempo real.

---

## 📂 Índice de Patrones y Tarjetas

### 🔍 Binary Search
- [**`binary-search-answer-on-range/`**](binary-search-answer-on-range/)
  - [1742E - Scuza](binary-search-answer-on-range/1742E_Scuza.md)
  - [RPC 08 Problem C - Don't Hunger Together](binary-search-answer-on-range/RPC-2026-08-C_Dont_Hunger_Together.md)

### 🔨 Brute Force & Search
- [**`brute-force-exhaustive-search/`**](brute-force-exhaustive-search/)
  - [1914D - Three Activities](brute-force-exhaustive-search/1914D_Three_Activities.md)
  - [RPC 08 Problem I - Missing Number](brute-force-exhaustive-search/RPC-2026-08-I_Missing_Number.md)

### 📈 Dynamic Programming
- [**`dp-linear-progression/`**](dp-linear-progression/)
  - [RPC 08 Problem B - Digit Translation](dp-linear-progression/RPC-2026-08-B_Digit_Translation.md)

### ♟️ Game Theory
- [**`game-theory-parity-turn/`**](game-theory-parity-turn/)
  - [1527B1 - Palindrome Game (easy version)](game-theory-parity-turn/1527B1_Palindrome_Game_easy_version.md)

### 🌐 Graphs & Trees
- [**`graph-shortest-path/`**](graph-shortest-path/)
  - [RPC 08 Problem K - Very Important Edge](graph-shortest-path/RPC-2026-08-K_Very_Important_Edge.md)

### ⚡ Greedy Paradigms
- [**`greedy-boundary-testing/`**](greedy-boundary-testing/)
  - [RPC 08 Problem E - ICPC Team Generation](greedy-boundary-testing/RPC-2026-08-E_ICPC_Team_Generation.md)
- [**`greedy-priority-based/`**](greedy-priority-based/)
  - [1157E - Minimum Array](greedy-priority-based/1157E_Minimum_Array.md)
  - [RPC 08 Problem A - Contest Advancement](greedy-priority-based/RPC-2026-08-A_Contest_Advancement.md)
- [**`greedy-sorting-based/`**](greedy-sorting-based/)
  - [RPC 08 Problem G - Lines Per Hour](greedy-sorting-based/RPC-2026-08-G_Lines_Per_Hour.md)
- [**`greedy-value-splitting/`**](greedy-value-splitting/)
  - [1859A - United We Stand](greedy-value-splitting/1859A_United_We_Stand.md)

### ⚙️ Implementation & Simulation
- [**`implementation-case-analysis/`**](implementation-case-analysis/)
  - [1845A - Forbidden Integer](implementation-case-analysis/1845A_Forbidden_Integer.md)
  - [RPC 08 Problem F - Is Y a Vowel?](implementation-case-analysis/RPC-2026-08-F_Is_Y_a_Vowel.md)

### 🔢 Mathematics & Number Theory
- [**`math-formula-development/`**](math-formula-development/)
  - [RPC 08 Problem D - Garden of Thorns](math-formula-development/RPC-2026-08-D_Garden_of_Thorns.md)
- [**`math-gap-analysis/`**](math-gap-analysis/)
  - [1853A - Desorting](math-gap-analysis/1853A_Desorting.md)
- [**`math-modular-arithmetic/`**](math-modular-arithmetic/)
  - [1837A - Grasshopper on a Line](math-modular-arithmetic/1837A_Grasshopper_on_a_Line.md)
- [**`math-number-theory/`**](math-number-theory/)
  - [1855B - Longest Divisors Interval](math-number-theory/1855B_Longest_Divisors_Interval.md)
  - [RPC 08 Problem H - Magnesium Supplementation](math-number-theory/RPC-2026-08-H_Magnesium_Supplementation.md)
- [**`math-parity-check/`**](math-parity-check/)
  - [1857A - Array Coloring](math-parity-check/1857A_Array_Coloring.md)
- [**`math-pigeonhole-principle/`**](math-pigeonhole-principle/)
  - [RPC 08 Problem L - Water Journal](math-pigeonhole-principle/RPC-2026-08-L_Water_Journal.md)

### 🔤 Strings & Text Processing
- [**`string-pattern-build/`**](string-pattern-build/)
  - [RPC 08 Problem J - Tip of Your Tongue](string-pattern-build/RPC-2026-08-J_Tip_of_Your_Tongue.md)
- [**`string-stack-processing/`**](string-stack-processing/)
  - [RPC 07 Problem H - You, You See What](string-stack-processing/RPC-2026-07-H_You_You_See_What.md)

---

## 📝 Estructura de una Tarjeta Flashcard

Toda tarjeta en esta colección sigue la estructura:

1. **Header:** Título, tipo, dificultad y tags normalizados.
2. **Key Insight (💡):** Declaración directa de 1-2 oraciones con la reducción esencial.
3. **Pattern Trigger:** Pistas explícitas en las restricciones o enunciado que indican la técnica.
4. **Breakthrough:** Detalle contraintuitivo o ajuste mental clave para no atascarse.
5. **Code Spotlight:** 3 a 8 líneas con la lógica pura de solución.
6. **Minimal Example:** Traza reducida que valida el funcionamiento de la invariante.
