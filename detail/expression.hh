#pragma once

namespace liegr {
namespace detail {

// SO(n)

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

// SE(n)

template <typename Expr>
class SEnExpression {
   public:
    auto rotation() const { return static_cast<const Expr&>(*this).rotation(); }
    auto translation() const {
        return static_cast<const Expr&>(*this).translation();
    }
};

template <typename LhsExpr, typename RhsExpr>
class SEnProduct : public SEnExpression<SEnProduct<LhsExpr, RhsExpr>> {
   public:
    SEnProduct(const LhsExpr& lhs, const RhsExpr& rhs) : lhs_(lhs), rhs_(rhs) {}

    auto rotation() const { return lhs_.rotation() * rhs_.rotation(); }
    auto translation() const {
        return lhs_.rotation() * rhs_.translation() + lhs_.translation();
    }

   private:
    const LhsExpr& lhs_;
    const RhsExpr& rhs_;
};

template <typename LhsExpr, typename RhsExpr>
SEnProduct<LhsExpr, RhsExpr> operator*(const SEnExpression<LhsExpr>& lhs,
                                       const SEnExpression<RhsExpr>& rhs) {
    return SEnProduct<LhsExpr, RhsExpr>(static_cast<const LhsExpr&>(lhs),
                                        static_cast<const RhsExpr&>(rhs));
}

template <typename Expr, typename Derived>
auto operator*(const SEnExpression<Expr>& lhs,
               const Eigen::MatrixBase<Derived>& rhs) {
    const Expr& lhs_expr = static_cast<const Expr&>(lhs);
    return lhs_expr.rotation() * rhs + lhs_expr.translation();
}

}  // namespace detail
}  // namespace liegr
