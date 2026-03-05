#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class Sheet : public SheetInterface {
public:
    Sheet() = default;
    ~Sheet() override;

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    const Cell* GetConcreteCell(Position pos) const;
    Cell* GetConcreteCell(Position pos);

    Cell& GetOrCreateCell(Position pos);

    static void ValidatePosition(Position pos);

    void InvalidateCacheFrom(Cell& changed);

private:
    // --- Хранилище ---
    using Key = std::int64_t;
    static Key MakeKey(Position pos);

    std::unordered_map<Key, std::unique_ptr<Cell>> cells_;

    Size printable_size_{0, 0};

private:
    // --- Вспомогательные методы для SetCell ---
    static std::vector<Position> ExtractReferencedCells(const Cell& tmp_cell);

    bool WouldIntroduceCycle(Position pos, const std::vector<Position>& new_refs) const;

    bool HasPathToTarget(Position start, Position target) const;

    void RebuildDependencies(Position pos, const std::vector<Position>& new_refs);

    // Утилиты печати и размера
    void UpdatePrintableSizeOnSet(Position pos, const std::string& text);
    void RecalculatePrintableSize();

    void PrintCells(std::ostream& output,
                    const std::function<std::string(const CellInterface*)>& get_cell_str) const;
};
