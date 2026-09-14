---
name: cp-problem-notes-generator
description: Ingests, analyzes, and documents competitive programming contests and problem sets (RPC, ICPC, Codeforces). Creates dedicated contest packages ([contest_id]/) with inputs/, solutions/, and outputs/notes/. Performs differential post-mortem on buggy team versions, authors concise autopsy notes for attempted problems, writes thorough pedagogical upsolving guides for unsolved problems, generates local contest README.md, and exports flashcards to cp-insights/.
---

# CP Contest & Problem Package Generator Skill

## Overview

Automates the complete end-to-end ingestion, autopsy, and study documentation for collegiate and online competitive programming contests (such as RPC, ICPC, Codeforces, NAQ).

**Core Philosophy:**
- **No Scattered Clutter:** Never dump files in the repo root. Every contest receives its own dedicated package directory (e.g. `rpc_08_2026/`).
- **Concise Autopsies for Solved Problems:** When a team solved or attempted a problem, focus on **where the bug was**, **what cognitive trap caused it**, and the **correcting logic**. Keep it brief and high-density.
- **Deep Pedagogical Upsolving for Unsolved Problems:** Thoroughly explain the underlying model, constraint clues, required algorithms, and clean implementation.
- **Flashcard Sync:** Every problem automatically generates a companion micro-insight card in `cp-insights/` following the `cp-quick-insight` schema.
- **Minimal Root Index:** The root `README.md` stays clean and minimal; full problem matrices and autopsies remain localized in the contest folder's `README.md`.
- **Zero Raw LaTeX:** Strictly use readable Markdown code spans (`O(N)`, `sqrt(N)`, `<=`, `>=`) instead of raw math delimiters (`$`, `\le`, `\sum`).

---

## Standard Contest Package Architecture

Whenever a contest problemset is processed, establish this clean layout:

```text
[contest_id]/                              # e.g., rpc_08_2026/
├── README.md                              # Local contest report, problem matrix & autopsy catalog
├── inputs/
│   ├── problemset/
│   │   └── Problemset_[ID].pdf            # Official PDF problem statement
│   ├── solutions/                         # Cleaned Accepted (AC) solutions: [Letter]_[Name].cpp
│   └── official_solutions/                # Editorial / reference solutions from authors
└── outputs/
    └── notes/                             # Individual problem study notes
        ├── A_[Problem_Title].md
        ├── B_[Problem_Title].md
        └── ...
```

---

## Workflow Steps

### Step 1: Ingestion & Hygiene
1. Create `[contest_id]/inputs/problemset/`, `inputs/solutions/`, `inputs/official_solutions/`, and `outputs/notes/`.
2. Move/copy the problem set PDF into `inputs/problemset/`.
3. Ingest team code files into `inputs/solutions/`:
   - Identify iterative attempts (e.g., `(1)`, `(2)`, `(3)`).
   - Perform differential analysis across versions to pinpoint exact bug triggers.
   - Retain **only the final Accepted (AC) version** renamed cleanly to `[Letter]_[Title].[ext]`.
   - Remove intermediate broken files after capturing bug differentials for the notes.
4. Save official / semi-official editorial solutions in `inputs/official_solutions/` with matching class/file names.

### Step 2: Problem Note Generation (`outputs/notes/`)

#### For Attempted / Solved Problems (Synthesized Autopsy):
- **Insight Clave**: 1-2 lines stating the core invariant.
- **Localización del Error**: Exact version-by-version diff (line number, flawed condition, overflow, stream print).
- **Patrón de Recurrencia / Sesgo Cognitivo**: Why programmers repeatedly fall into this trap (e.g., *Hardcoded Sample Syndrome*, *Silent 32-bit Overflow*, *Premature Stream Output*).
- **Lógica Correcta & Código Limpio**: Clean explanation of the fix and reference code.

#### For Unsolved Problems (Pedagógica & Upsolving):
- **Deconstrucción del Enunciado**: Real problem essence stripped of story distractions.
- **Pistas en las Restricciones (*Pattern Triggers*)**: Why constraints (e.g., `N <= 10^5`, `L <= 5`, `10^-9 precision`) signal the specific technique.
- **Técnicas y Conceptos Teóricos**: Clear mathematical/algorithmic model.
- **Estrategia de Implementación Limpia**: Step-by-step algorithm and reference implementation.

### Step 3: Local Contest Master Report (`[contest_id]/README.md`)
Generate a comprehensive contest dashboard containing:
1. Executive summary (Problems Solved / Upsolved, Date, Rules).
2. Complete Problem Matrix table (Letter, Title, Contest Status, Category, Complexity, Link to note in `outputs/notes/`).
3. **Catálogo de Antipatrones Cometidos en Vivo**: Exhaustive post-mortem of cognitive pitfalls committed during the contest.

### Step 4: Companion Insights Export (`cp-insights/`)
Export an insight card for every problem into `cp-insights/[algorithm-subtype]/` adhering to `cp-quick-insight` schema, and append breakthroughs to `breakthroughs.md`.

### Step 5: Root Index Integration
Add a single concise row to the `## Secciones` or Contest Directory table in the root `README.md`. **Never paste multi-row tables or bulky problem matrices into the root `README.md`**.

---

## Formatting Guardrails
- **Language**: English for internal orchestration and tool calls; Spanish for user-facing notes and communications (unless explicitly requested otherwise).
- **Zero LaTeX Syntax**: Use `O(N log N)`, `O(sqrt(N))`, `<=`, `>=`, `10^11`, `mid = (low + high) / 2`.
- **Clean Java Classes**: Ensure Java official solutions match their file names (`public class B_DigitTranslation` in `B_DigitTranslation.java`).
