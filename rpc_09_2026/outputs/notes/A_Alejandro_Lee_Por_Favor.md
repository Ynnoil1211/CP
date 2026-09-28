# Problema A: Alejandro, lee por favor

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Carlos Alberto Salazar Meza (UFPS Cúcuta, Colombia)
- **Dificultad Estimada:** Fácil (Div 3B / Div 2A)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [A_Alejandro_Lee_Por_Favor.py](../../inputs/solutions/A_Alejandro_Lee_Por_Favor.py)

---

## 1. Lógica y Enfoque del Problema

El problema presenta un algoritmo de cifrado estilo César con desplazamiento dinámico aplicado carácter a carácter sobre una secuencia de `N` palabras en minúsculas:

1. **Variables de estado del cifrador:**
   - Un contador global de desplazamiento `c`, inicializado en `0`.
   - Un arreglo de frecuencias para las 26 letras `count[0..25]`, inicializado en ceros.
2. **Proceso de descifrado (proceso inverso):**
   - El texto cifrado nos da cada carácter escrito `E`.
   - Durante la escritura, la letra original `L` se reemplazó por la letra que estaba `c` posiciones adelante en el alfabeto: `E = (L + c) mod 26`.
   - Por tanto, para recuperar la letra original:
     `L = (E - c) mod 26 = (E - c + 26) mod 26`.
   - Inmediatamente tras descifrar la letra original `L`, se actualiza la frecuencia de la letra original: `count[L] += 1`.
   - Si `count[L]` es múltiplo exacto de `K` (`count[L] % K == 0`), el contador global `c` se incrementa en 1 (`c += 1`).
   - El nuevo valor de `c` afectará a las letras posteriores.

El objetivo es reconstruir e imprimir las `N` palabras originales respetando el mismo orden y separadas por espacios simples.

---

## 2. Análisis Diferencial y Puntos Críticos

En la implementación en Python [A_Alejandro_Lee_Por_Favor.py](../../inputs/solutions/A_Alejandro_Lee_Por_Favor.py):

- **Lectura completa por lotes:** Se utiliza `sys.stdin.read().split()` para leer simultáneamente las `N` palabras. Esto evita el overhead de múltiples llamadas a `input()` y garantiza `O(|S|)` tiempo total.
- **Aritmética modular negativa:** En Python, el operador `% 26` maneja números negativos de forma matemática (ej. `-1 % 26 = 25`), mientras que en C++ `(e - c) % 26` puede producir valores negativos, requiriendo `(e - c % 26 + 26) % 26`.
- **Actualización de `c`:** La condición de incremento debe evaluarse sobre la frecuencia de la **letra original descifrada** `L`, jamás sobre la letra cifrada `E`.

---

## 3. Trampas Cognitivas Recurrentes

1. **Confusión de la variable observada (*The Encrypted State Fallacy*):**
   Un error común es incrementar la frecuencia de `E` (la letra leída del input) en vez de `L` (la letra descifrada). La especificación establece explícitamente: *"se incrementa en uno el contador de apariciones de L (la letra original, no la que quedó escrita)"*.
2. **I/O lenta con cadenas grandes:**
   La suma de longitudes de las palabras alcanza `10^6`. La concatenación cuadrática de strings (`str += char`) en un bucle provocaría `Time Limit Exceeded` (TLE). Se debe acumular caracteres en una lista y unirlos con `''.join()` y luego `' '.join()`.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(|S|)` donde `|S| <= 10^6` es la cantidad total de caracteres. Cada letra se procesa en `O(1)`.
- **Complejidad Espacial:** `O(|S|)` para almacenar las palabras y la lista de caracteres recuperados.

```python
import sys

def main():
    data = sys.stdin.read().split()
    if not data:
        return

    n = int(data[0])
    k = int(data[1])
    words = data[2 : 2 + n]

    c = 0
    count = [0] * 26
    a_ord = ord('a')
    result_words = []

    for w in words:
        out_chars = []
        for ch in w:
            e = ord(ch) - a_ord
            l = (e - c) % 26
            out_chars.append(chr(a_ord + l))
            count[l] += 1
            if count[l] % k == 0:
                c += 1
        result_words.append(''.join(out_chars))

    print(' '.join(result_words))

if __name__ == "__main__":
    main()
```
