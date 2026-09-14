# Problema F: Is Y a Vowel?

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Muy Fácil (Div 3A)
- **Estado en Concurso:** Resuelto en primer intento (AC directo)
- **Archivos de Referencia:**
  - Solución de Equipo: `inputs/solutions/Vowel.cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/F_Vowel.cpp`

---

## 1. Lógica y Enfoque del Problema

Se recibe una palabra en inglés con letras minúsculas (longitud hasta 50).
Se solicita imprimir dos números enteros separados por un espacio:
1. La cantidad de vocales considerando únicamente {a, e, i, o, u}.
2. La cantidad de vocales considerando {a, e, i, o, u} junto con la letra y.

Basta con realizar un recorrido lineal simple sobre la cadena, manteniendo dos acumuladores:
- Contador 1: incrementa si el carácter está en `"aeiou"`.
- Contador 2: incrementa si está en `"aeiou"` o es `'y'`. (Equivalente a Contador 1 + conteo de `'y'`).

---

## 2. Dónde Estuvo el Error en Versiones Previas

- **El equipo obtuvo AC directo:** El código `Vowel.cpp` resolvió el problema limpiamente en el primer intento.
- **Riesgos latentes evitados:** En este tipo de problemas triviales, los errores comunes suelen ser:
  - Manejo innecesario de mayúsculas/minúsculas sin leer que la entrada garantizaba caracteres en minúscula.
  - Imprimir en líneas separadas en lugar de separados por un espacio según el formato exacto requerido.

---

## 3. Trampa Cognitiva Recurrente

1. **Sobre-ingeniería sintáctica:**  
   Intentar utilizar expresiones regulares pesadas (`std::regex`) en C++, las cuales tienen un overhead de compilación y ejecución innecesario, cuando una simple función auxiliar o `find` sobre una cadena constante es instantánea.
2. **Confusión de formato de salida:**  
   Fallar por no leer si la salida requería dos líneas o dos enteros en una misma línea separados por un espacio.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Vowel.cpp`):**
  ```cpp
  const string vowels = "aeiouAEIOU";
  int res = 0, res1 = 0;
  for (int i = 0; i < s.length(); i++) {
      if (vowels.find(s[i]) != string::npos) {
          res++;
          res1++;
      }
      if (s[i] == 'y') res1++;
  }
  cout << res << " " << res1 << endl;
  ```
- **Oficial (`F_Vowel.cpp` - Arup Guha):**
  Declara una función `isVowel(char c)` con un `switch` o cadena `"aeiou"`, suma 1 a ambos contadores para las 5 vocales, y suma 1 al segundo contador si c == 'y'.
- **Complejidad:** O(|S|) tiempo y O(1) memoria adicional en ambos.