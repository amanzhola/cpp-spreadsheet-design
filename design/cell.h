#pragma once

#include "common.h"
#include "formula.h"

#include <memory>
#include <optional>
#include <set>
#include <string>
#include <utility>
#include <vector>

class Sheet;

class Cell : public CellInterface {
public:
    explicit Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;
    std::vector<Position> GetReferencedCells() const override;

    const std::vector<Position>& GetReferencedCellsRaw() const noexcept;

    const std::set<Cell*>& GetDependents() const noexcept;

    void AddDependent(Cell& cell);
    void RemoveDependent(Cell& cell);

    void SetReferencedCells(std::vector<Position> refs);

    void InvalidateCache() const;
    bool HasCache() const noexcept;

private:
    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;

    Sheet& sheet_;
    std::unique_ptr<Impl> impl_;

    mutable std::optional<Value> cache_;

    std::vector<Position> referenced_cells_;
    std::set<Cell*> dependents_;
};
