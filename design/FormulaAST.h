#pragma once

#include "FormulaLexer.h"
#include "common.h"

#include <forward_list>
#include <functional>
#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace ASTImpl {
class Expr;
}  // namespace ASTImpl

class ParsingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class FormulaAST {
public:
    using CellValueGetter = std::function<double(Position)>;

    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr);

    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr,
                        std::vector<Position> referenced_cells);

    FormulaAST(FormulaAST&&) noexcept = default;
    FormulaAST& operator=(FormulaAST&&) noexcept = default;

    FormulaAST(const FormulaAST&) = delete;
    FormulaAST& operator=(const FormulaAST&) = delete;

    ~FormulaAST();

    double Execute(const CellValueGetter& get_value) const;

    void Print(std::ostream& out) const;
    void PrintFormula(std::ostream& out) const;

    const std::vector<Position>& GetReferencedCells() const noexcept;

private:
    std::unique_ptr<ASTImpl::Expr> root_expr_;
    std::vector<Position> referenced_cells_;  // отсортировано, без повторов
};

FormulaAST ParseFormulaAST(std::istream& in);
FormulaAST ParseFormulaAST(const std::string& in_str);
