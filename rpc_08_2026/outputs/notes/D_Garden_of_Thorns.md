# Problema D: Garden of Thorns

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Difícil (Div 1C / Div 2F)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Solución Oficial: `inputs/official_solutions/D_Garden.java`

---

## 1. Explicación Pedagógica del Problema

Eddy posee un jardín rectangular en el plano cartesiano delimitado por $[0, w] \times [0, h]$.
En el jardín hay $N$ plantas específicas ubicadas en coordenadas $(x_i, y_i)$, cada una con un valor intrínseco $v_i$.
Su asistente Zyra planta un círculo de espinas de radio $r$ centrado en un punto aleatorio $(X, Y)$ distribuido de manera uniforme continua en el interior del jardín $[0, w] \times [0, h]$.
Una planta $i$ queda protegida si cae estrictamente dentro del círculo de espinas; es decir:
$$\text{dist}((X, Y), (x_i, y_i)) = \sqrt{(X - x_i)^2 + (Y - y_i)^2} < r$$

**Objetivo:** Calcular el valor esperado del total de plantas protegidas: $\mathbb{E}\left[\sum_{i=1}^N v_i \cdot \mathbf{1}_{\{\text{planta } i \text{ protegida}\}}\right]$, con un error absoluto o relativo no mayor a $10^{-9}$.

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **Restricción diminuta de plantas ($1 \le N \le 10$):**  
  Tener a lo sumo 10 plantas es la pista definitiva de que cada planta puede procesarse de forma completamente independiente y que el cálculo geométrico por planta puede ser elaborado sin riesgo de sobrepasar el tiempo límite.
- **Linealidad de la Esperanza:**  
  La variable aleatoria "valor total protegido" es una suma ponderada de variables indicadoras de protección individual.
  Por linealidad de la esperanza:
  $$\mathbb{E}[V] = \sum_{i=1}^N v_i \cdot \mathbb{P}(\text{planta } i \text{ queda protegida})$$
  ¡No se necesita calcular probabilidades conjuntas de protección ni lidiar con la correlación entre plantas!

- **Geometrización de la Probabilidad:**  
  La condición $\text{dist}((X, Y), (x_i, y_i)) < r$ es equivalente a decir que el centro aleatorio $(X, Y)$ debe pertenecer al disco abierto $D((x_i, y_i), r)$ de radio $r$ centrado en la planta $(x_i, y_i)$.
  Dado que el centro $(X, Y)$ se escoge con distribución uniforme en el rectángulo $\mathcal{R} = [0, w] \times [0, h]$ de área $w \cdot h$:
  $$\mathbb{P}(\text{planta } i \text{ queda protegida}) = \frac{\text{Área}(D((x_i, y_i), r) \cap [0, w] \times [0, h])}{w \cdot h}$$
  El problema se reduce puramente a: **Calcular el área de intersección entre un círculo de radio $r$ centrado en $(x_i, y_i)$ y un rectángulo alineado con los ejes $[0, w] \times [0, h]$**.

---

## 3. Técnica Algorítmica: Intersección Círculo-Rectángulo

Para una planta en $(x, y)$ con radio $r$:

### Casos Extremos Inmediatos
1. **Círculo Completamente Contenido:**
   Si $x \ge r \land y \ge r \land w - x \ge r \land h - y \ge r$, el disco está totalmente dentro del rectángulo:
   $$\text{Área} = \pi r^2$$
2. **Rectángulo Completamente Contenido en el Círculo:**
   Si las 4 esquinas del rectángulo están a distancia $\le r$ del centro:
   $$\text{Área} = w \cdot h$$

### Descomposición General en Triángulos y Sectores Circulares
Cuando el disco intersecta los bordes del rectángulo:
1. **Identificar segmentos secantes:**  
   Para cada uno de los 4 bordes del rectángulo (arriba $Y=h$, abajo $Y=0$, izquierda $X=0$, derecha $X=w$), calculamos los puntos de intersección con la circunferencia $(X-x)^2 + (Y-y)^2 = r^2$ acotados al segmento del borde respectivo.
2. **Suma de Regiones:**  
   El área interior al rectángulo se descompone en:
   - **Triángulos rectángulos/isósceles** formados desde el centro del círculo hacia los bordes secantes planos del rectángulo.
   - **Sectores circulares** $(\frac{1}{2} r^2 \Delta \theta)$ correspondientes a los arcos que no son cortados por los bordes y conectan los extremos de las proyecciones.
3. Alternativamente, este cálculo puede resolverse con integración analítica o el Teorema de Green / fórmula del área con funciones trigonométricas ($\arcsin$).

---

## 4. Estrategia de Implementación y Código de Referencia

En la solución oficial de Arup Guha (`inputs/official_solutions/D_Garden.java`):

```java
// Contribución de cada planta
double res = 0;
for (int i = 0; i < n; i++) {
    int x = stdin.nextInt();
    int y = stdin.nextInt();
    int v = stdin.nextInt();
    double area = getArea(x, y, r);
    res += v * area / (w * h);
}
System.out.printf("%.15f\n", res);
```

En `getArea(x, y, r)`:
- Verifica los casos base triviales ($\pi r^2$ o $w \cdot h$).
- Proyecta triángulos en los 4 bordes donde la distancia a la pared es menor que $r$ ($h-y < r$, $x < r$, $y < r$, $w-x < r$) sumando el área del triángulo $(x_2 - x_1) \cdot \text{dist} \cdot \frac{1}{2}$.
- Colecciona los puntos de corte en una lista circular `pts`, calcula los ángulos angulares vía `Math.atan2` y suma los sectores circulares intermedios: $\frac{1}{2} r^2 (\alpha_2 - \alpha_1)$.

### Complejidad
- **Tiempo:** $O(N)$ operaciones con $N \le 10$. El tiempo de cálculo es imperceptible ($< 0.01$ s).
- **Espacio:** $O(1)$ memoria auxiliar.
