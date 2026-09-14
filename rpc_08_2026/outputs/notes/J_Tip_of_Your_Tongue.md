# Problema J: Tip of Your Tongue

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Media-Alta (Div 1B / Div 2E)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Solución Oficial: `inputs/official_solutions/J_Tongue.java`

---

## 1. Explicación Pedagógica del Problema

Se tiene un diccionario con $N$ palabras distintas en minúsculas. Se deben responder $Q$ consultas sobre el diccionario ($N, Q \le 2 \cdot 10^5$, con la suma total de caracteres en palabras y consultas acotada por $10^6$).
Cada consulta proporciona una operación $op \in \{\text{"AND"}, \text{"OR"}, \text{"XOR"}\}$ y dos patrones de texto: un prefijo $p$ y un sufijo $s$, con la propiedad crítica de que **ambos tienen exactamente la misma longitud**: $|p| = |s| = L$.

Las operaciones preguntan cuántas palabras del diccionario cumplen:
1. **`AND p s`:** Palabras que tienen a $p$ como prefijo **Y** a $s$ como sufijo.
2. **`OR p s`:** Palabras que tienen a $p$ como prefijo **O** a $s$ como sufijo.
3. **`XOR p s`:** Palabras que cumplen exactamente una de las dos condiciones (prefijo $p$ o sufijo $s$, pero no ambas a la vez).

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **Restricción unificadora $|p| = |s| = L$:**  
  Que el prefijo y sufijo consultados siempre compartan la misma longitud $L$ simplifica radicalmente la indexación. Para cada palabra $W$ del diccionario de longitud $M$, para cada posible tamaño de consulta $L \le M$, el prefijo de longitud $L$ ($W[0 \dots L-1]$) y el sufijo de longitud $L$ ($W[M-L \dots M-1]$) quedan determinados unívocamente.
- **Principio de Inclusión-Exclusión (PIE):**  
  Sean:
  - $A$: conjunto de palabras con prefijo $p$ $\implies |A| = N(p)$.
  - $B$: conjunto de palabras con sufijo $s$ $\implies |B| = N(s)$.
  - $A \cap B$: conjunto de palabras con prefijo $p$ Y sufijo $s$ simultáneamente $\implies |A \cap B| = N(p \land s)$.

  Las 3 operaciones booleanas se expresan directamente en términos de estas tres cantidades fundamentales:
  $$\text{AND}(p, s) = |A \cap B|$$
  $$\text{OR}(p, s) = |A \cup B| = |A| + |B| - |A \cap B|$$
  $$\text{XOR}(p, s) = |A \triangle B| = |A| + |B| - 2|A \cap B|$$
  Por tanto, **toda consulta se resuelve de inmediato si podemos consultar en $O(1)$ los valores de $|A|$, $|B|$ y $|A \cap B|$**.

- **Suma de longitudes $\le 10^6$:**  
  Una palabra de longitud $M$ tiene exactamente $M$ prefijos y $M$ sufijos. La suma de todos los prefijos y sufijos generados sobre todo el diccionario es a lo sumo $10^6$.

---

## 3. Técnica Algorítmica: Doble Hash Polinomial + Tablas Hash por Longitud

Para evitar problemas de memoria y colisiones:
1. **Doble Hashing Polinomial:**  
   Se eligen dos primos grandes (por ejemplo $P_1 \approx 10^9+7$, $P_2 \approx 10^9+9$) y una base polinomial (por ejemplo $B = 29$ o $31$).
   Para una palabra $W$, se precalculan los hashes de todos sus prefijos y sufijos en $O(|W|)$.
2. **Emparejamiento de Claves:**
   Para cada longitud $L \in [1, |W|]$:
   - Clave de Prefijo: $\text{hash}(W[0 \dots L-1])$
   - Clave de Sufijo: $\text{hash}(W[|W|-L \dots |W|-1])$
   - Clave Conjunta (AND): Combinación única de $(\text{hash}(W[0 \dots L-1]), \text{hash}(W[|W|-L \dots |W|-1]))$.
3. **Tablas Hash Separadas por Longitud:**
   Mantener un arreglo de tablas hash indexadas por longitud $L$:
   - `pre[L][hash_p]`: Frecuencia del prefijo de longitud $L$.
   - `suf[L][hash_s]`: Frecuencia del sufijo de longitud $L$.
   - `and[L][hash_conjunto]`: Frecuencia de palabras con ambos a la vez.

---

## 4. Estrategia de Implementación y Código de Referencia

La solución oficial de Arup Guha (`inputs/official_solutions/J_Tongue.java`) implementa este diseño:

```java
// Para cada palabra en el diccionario:
for (int j = 0; j < n; j++) { // j representa la longitud L - 1
    // Actualiza hashes rolling en hpre, hsuf y hand
    long key1 = (hpre[0] << 31) + hpre[1]; // Prefijo
    long key2 = (hsuf[0] << 31) + hsuf[1]; // Sufijo
    long key3 = (hand[0] << 31) + hand[1]; // Prefijo + Sufijo
    
    pre[j].put(key1, pre[j].getOrDefault(key1, 0) + 1);
    suf[j].put(key2, suf[j].getOrDefault(key2, 0) + 1);
    and[j].put(key3, and[j].getOrDefault(key3, 0) + 1);
}

// Al responder cada consulta:
int a1 = pre[L-1].getOrDefault(key1, 0);
int a2 = suf[L-1].getOrDefault(key2, 0);
int a3 = and[L-1].getOrDefault(key3, 0);

if (type.equals("AND")) 
    output(a3);
else if (type.equals("OR")) 
    output(a1 + a2 - a3);
else if (type.equals("XOR")) 
    output(a1 + a2 - 2 * a3);
```

### Complejidad
- **Preprocesamiento:** $O(\sum |W|) \le 10^6$ operaciones de hashing e inserción en hash tables.
- **Consultas:** $O(|p|)$ para calcular los hashes de los patrones y $O(1)$ promedio por búsqueda.  
  Total de tiempo en consultas: $O(\sum |p|) \le 10^6$.
- **Espacio:** $O(\sum |W|)$ estados en las tablas hash.
