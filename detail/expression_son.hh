#pragma once

#include <eigen3/Eigen/Core>

namespace liegr {
namespace detail {

// Forward declare inverse expression for convenience inverse() method on base
// SOnExpression class.
template <typename Expr>
class SOnInverse;

template <typename Expr>
class SOnExpression {
   public:
    auto matrix() const { return static_cast<const Expr&>(*this).matrix(); }

    SOnInverse<Expr> inverse() const {
        return SOnInverse<Expr>(static_cast<const Expr&>(*this));
    }
};

template <typename Expr>
class SOnInverse : public SOnExpression<SOnInverse<Expr>> {
   public:
    SOnInverse(const Expr& expr) : expr_(expr) {}
    auto matrix() const { return expr_.matrix().transpose(); }

   private:
    const Expr& expr_;
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
    EIGEN_STATIC_ASSERT_SAME_MATRIX_SIZE(decltype(lhs.matrix()),
                                         decltype(rhs.matrix()));

    return SOnProduct<LhsExpr, RhsExpr>(static_cast<const LhsExpr&>(lhs),
                                        static_cast<const RhsExpr&>(rhs));
}

template <typename Expr, typename Derived>
auto operator*(const SOnExpression<Expr>& lhs,
               const Eigen::MatrixBase<Derived>& rhs) {
    // TODO Support allowing multiple vectors to be stacked horizontally in rhs?
    EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived);
    return static_cast<const Expr&>(lhs).matrix() * rhs;
}

}  // namespace detail
}  // namespace liegr
