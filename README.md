# Spreadsheet Engine Design

## 🇷🇺 Описание

Этот репозиторий содержит **архитектуру и дизайн движка электронной таблицы (mini Excel)**, реализованного на C++.

Здесь описаны ключевые компоненты системы, механизмы работы и архитектурные решения:

- формулы и их вычисление (AST);
- граф зависимостей между ячейками;
- кэширование значений;
- инвалидация кэша;
- обнаружение циклических зависимостей;
- безопасное обновление ячеек (two-phase commit).

👉 Основная реализация проекта находится здесь:  
**https://github.com/<your-username>/cpp-spreadsheet**

---

## 🇬🇧 Description

This repository contains the **design and architecture of a C++ spreadsheet engine (mini Excel)**.

It describes the core system components and key mechanisms:

- formula parsing and evaluation (AST);
- dependency graph;
- caching and cache invalidation;
- cycle detection;
- safe cell updates (two-phase commit).

👉 Main implementation:  
**https://github.com/<your-username>/cpp-spreadsheet**

---

## 🧠 Архитектура / Architecture

### 🔹 FormulaAST

- дерево разбора выражений (Abstract Syntax Tree);
- вычисление формулы через callback;
- хранение списка зависимых ячеек.

```cpp
double Execute(const CellValueGetter& get_value) const;
````

---

### 🔹 Cell

Отвечает за:

* хранение текста / формулы;
* вычисление значения;
* кэш;
* связи зависимостей.

Ключевые поля:

* `referenced_cells_` — зависимости;
* `dependents_` — обратные зависимости;
* `cache_` — кэш результата.

---

### 🔹 Formula

Интерфейс формулы:

* вычисляет значение (`double` или ошибка);
* возвращает выражение;
* предоставляет список зависимых ячеек.

---

### 🔹 Sheet

Центральный компонент системы.

Отвечает за:

* хранение всех ячеек;
* управление dependency graph;
* проверку циклов;
* пересчёт значений;
* инвалидацию кэша;
* вывод данных.

---

## 🔗 Dependency Graph

Каждая ячейка — вершина графа.

Связи:

* A → B означает "A зависит от B"

Используется для:

* обнаружения циклов;
* обновления зависимых ячеек;
* оптимизации пересчёта.

---

## ⚙️ Ключевые механизмы

### 🔸 Cache Invalidation

При изменении ячейки:

1. очищается её кэш;
2. рекурсивно очищаются все зависимые ячейки.

📄 `cache_invalidation.pdf`

---

### 🔸 Cycle Detection

Перед установкой формулы:

* проверяется, создаёт ли она цикл;
* используется обход графа (DFS).

📄 `cyclic_dependencies.pdf`

---

### 🔸 Formula Calculation

* выражение парсится в AST;
* вычисляется через значения ячеек;
* изолировано от `Sheet`.

📄 `formula_calculation.pdf`

---

### 🔸 SetCell (Two-Phase Commit)

Обновление ячейки происходит в два этапа:

#### Phase 1 — подготовка

* парсинг формулы;
* извлечение зависимостей;
* проверка цикла.

#### Phase 2 — применение

* обновление ячейки;
* перестроение графа;
* инвалидация кэша.

📄 `new_cell.pdf`

---

## 📂 Содержимое репозитория

* архитектура компонентов (`Cell`, `Sheet`, `Formula`, `AST`);
* описание алгоритмов;
* PDF-документы:

  * cache invalidation
  * cycle detection
  * formula evaluation
  * cell update process

---

## 🎯 Цель проекта

* показать архитектуру spreadsheet engine;
* продемонстрировать работу dependency graph;
* реализовать корректное кэширование;
* обеспечить безопасное обновление данных;
* разделить ответственность компонентов.

---

## 🧪 Что демонстрирует

* AST (Abstract Syntax Tree);
* dependency graph;
* cycle detection;
* cache invalidation;
* архитектуру системы уровня реального приложения.

---

## 🚀 Использование

Репозиторий предназначен для:

* изучения архитектуры;
* подготовки к собеседованиям;
* демонстрации навыков system design.

---

## 🔗 Связанный репозиторий

👉 Основная реализация:

[https://github.com/](https://github.com/)<your-username>/cpp-spreadsheet

---

## 👨‍💻 Автор
Amanzhol
C++ / Qt / System Design
