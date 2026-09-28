# Problema F: Flipando colores con la DIAN

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** María Alexandra Velásquez Jaimes (UFPS Cúcuta, Colombia)
- **Dificultad Estimada:** Avanzada (Div 1C / Div 2E)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [F_Flipando_Colores_Con_La_DIAN.cpp](../../inputs/solutions/F_Flipando_Colores_Con_La_DIAN.cpp)
  - Solución Oficial: [F_Flipando_Colores.cpp](../../inputs/official_solutions/F_Flipando_Colores.cpp)

---

## 1. Lógica y Enfoque del Problema

Se deben programar `N` trámites (`N <= 10^6`). Cada trámite `i` tiene una duración `p_i` y una penalización diaria `w_i`. Si un trámite finaliza en el instante `C_i = sum_{j precede i} p_j`, el costo total es `sum_{i=1}^N C_i * w_i`.
Existen `M` restricciones de precedencia donde `a` no puede cerrarse antes que `b` (`b` debe procesarse antes que `a`). Cada trámite depende a lo sumo de un único prerrequisito y no hay ciclos, formando un **bosque de árboles dirigidos**.

### Fundamento Teórico: Regla de Smith y Contracción de Lawler (1978)

1. **Regla de Smith (sin precedencias):**
   Entre dos trámites independientes `A` y `B`, procesar `A` antes que `B` genera un costo cruzado `p_A * w_B`. Procesar `B` antes que `A` genera `p_B * w_A`.
   Es preferible procesar `A` antes si:
   `p_A * w_B < p_B * w_A  <=>  w_A / p_A > w_B / p_B`.
   La cantidad `rho_i = w_i / p_i` es la **densidad** o índice de Smith.
2. **Teorema de Contracción de Lawler:**
   Sea `u` el nodo que **maximiza la densidad `w_u / p_u` entre todos los nodos que tienen un padre `par(u)`**.
   En cualquier programación óptima, `u` debe ejecutarse **inmediatamente después** de finalizar `par(u)`. No existe ventaja en intercalar tareas entre ellos.
   Por tanto, `par(u)` y `u` pueden colapsarse en un único macro-nodo:
   - Duración: `P[par] += P[u]`.
   - Peso: `W[par] += W[u]`.
   - Costo acumulado adicional por retrasar `u`: `P[par_antes] * W[u]`.
3. **Súper-Nodo Raíz 0:**
   Se unifica el bosque introduciendo un nodo ficticio `0` con `P[0] = 0, W[0] = 0`, al que se conectan todos los trámites sin dependencia. El nodo `0` **nunca entra a la cola de prioridad**; únicamente recibe fusiones de los macro-nodos más densos.

---

## 2. Estructuras de Datos y Cotas Aritméticas

- **DSU con Compresión de Caminos:** Mantiene el representante del macro-nodo actual tras sucesivas fusiones.
- **Priority Queue con Eliminación Perezosa (Lazy Deletion):** El heap almacena tripletas `(w, p, u)`. Al extraer, si `find_set(u) != u` o los valores no coinciden con los vigentes, se descarta.
- **Comparación Exacta:**
  `w1 / p1 > w2 / p2  <=>  w1 * p2 > w2 * p1`.
- **Cotas Numéricas:**
  `sum p_i <= 2 * 10^9`, `sum w_i <= 2 * 10^9`.
  El producto cruzado máximo es `2 * 10^9 * 2 * 10^9 = 4 * 10^{18}`.
  Como un entero de 64 bits con signo (`long long`) soporta hasta `9.22 * 10^{18}`, `long long` nativo cubre todos los cálculos sin requerir `__int128`.

---

## 3. Trampas Cognitivas Recurrentes

1. **Greedy Ingenuo en Raíces:**
   Tomar vorazmente la raíz disponible con mayor `w / p`. Falla cuando una raíz de baja densidad bloquea a un hijo con densidad descomunal. Lawler demuestra que la contracción debe hacerse bottom-up desde el nodo de mayor densidad del sistema hacia su padre.
2. **Reinsertar el Súper-Nodo 0 al Heap:**
   Si el nodo 0 entrara a la cola de prioridad, competiría consigo mismo y distorsionaría la secuencia temporal.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(N log N)`. A lo sumo `2N` inserciones en el heap y operaciones de DSU en `O(alpha(N))`. Procesa `10^6` elementos en `~0.45 s` en C++ (límite: 4.0 s).
- **Complejidad Espacial:** `O(N)`. Arreglos estáticos y el heap consumen `~56 MB`, muy por debajo de los 256 MB permitidos.

```cpp
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000005;

struct Block {
    long long w, p;
    int id;
    bool operator<(const Block& other) const {
        return w * other.p < other.w * p;
    }
};

int parent_dsu[MAXN];
int parent_tree[MAXN];
long long P[MAXN];
long long W[MAXN];

int find_set(int v) {
    if (v == parent_dsu[v]) return v;
    return parent_dsu[v] = find_set(parent_dsu[v]);
}

void solve() {
    int n;
    while (cin >> n) {
        long long total_cost = 0;
        P[0] = 0; W[0] = 0;
        parent_dsu[0] = 0; parent_tree[0] = 0;

        for (int i = 1; i <= n; ++i) {
            cin >> P[i];
            parent_dsu[i] = i;
            parent_tree[i] = 0;
        }

        for (int i = 1; i <= n; ++i) {
            cin >> W[i];
            total_cost += P[i] * W[i];
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            parent_tree[a] = b;
        }

        priority_queue<Block> pq;
        for (int i = 1; i <= n; ++i) pq.push({W[i], P[i], i});

        while (!pq.empty()) {
            auto [w, p, u] = pq.top();
            pq.pop();

            if (find_set(u) != u || W[u] != w || P[u] != p) continue;

            int par = find_set(parent_tree[u]);
            total_cost += P[par] * W[u];
            P[par] += P[u];
            W[par] += W[u];
            parent_dsu[u] = par;

            if (par != 0) pq.push({W[par], P[par], par});
        }

        cout << total_cost << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
```
