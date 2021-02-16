#pragma once

#include <eigen3/Eigen/Core>

namespace liegr {
namespace detail {

template <typename Expr>
class SOnExpression {
   public:
    auto matrix() const { return static_cast<const Expr&>(*this).matrix(); }
};

template <typename LhsExpr, typename RhsExpr>
class SOnProduct : public SOnExpression<SOnProduct<LhsExpr, RhsExpr>> {
   public:
    SOnProduct(const LhsExpr& lhs, const RhsExpr& rhs) : lhs_(lhs), rhs_(rhs) {}

    auto matrix() const { return lhs_.matrix() * rhs_.matrix(); }

   private:
    const LhsExpr& lhs_;
    const RhsExpr& rhs_;
};

template <typename LhsExpr, typename RhsExpr>
SOnProduct<LhsExpr, RhsExpr> operator*(const SOnExpression<LhsExpr>& lhs,
                                       const SOnExpression<RhsExpr>& rhs) {
    return SOnProduct<LhsExpr, RhsExpr>(static_cast<const LhsExpr&>(lhs),
                                        static_cast<const RhsExpr&>(rhs));
}

template <typename Expr, typename Derived>
auto operator*(const SOnExpression<Expr>& lhs,
               const Eigen::MatrixBase<Derived>& rhs) {
    return static_cast<const Expr&>(lhs).matrix() * rhs;
}

}  // namespace detail
}  // namespace liegr
