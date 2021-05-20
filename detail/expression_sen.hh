#pragma once

#include <eigen3/Eigen/Core>

namespace liegr {
namespace detail {

// Forward declare inverse expression for convenience inverse() method on base
// SEnExpression class.
template <typename Expr>
class SEnInverse;

template <typename Expr>
class SEnExpression {
   public:
    auto rotation() const { return static_cast<const Expr&>(*this).rotation(); }
    auto translation() const {
        return static_cast<const Expr&>(*this).translation();
    }

    SEnInverse<Expr> inverse() const {
        return SEnInverse<Expr>(static_cast<const Expr&>(*this));
    }
};

template <typename Expr>
class SEnInverse : public SEnExpression<SEnInverse<Expr>> {
   public:
    SEnInverse(const Expr& expr) : expr_(expr) {}
    auto rotation() const { return expr_.rotation().inverse(); }
    auto translation() const { return -(rotation() * expr_.translation()); }

   private:
    const Expr& expr_;
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
    // TODO Why doesn't this check work?
    // EIGEN_STATIC_ASSERT_SAME_MATRIX_SIZE(decltype(lhs.rotation().matrix()),
    //                                      decltype(rhs.rotation().matrix()));
    // EIGEN_STATIC_ASSERT_SAME_VECTOR_SIZE(decltype(lhs.translation()),
    //                                      decltype(rhs.translation()));

    return SEnProduct<LhsExpr, RhsExpr>(static_cast<const LhsExpr&>(lhs),
                                        static_cast<const RhsExpr&>(rhs));
}

template <typename Expr, typename Derived>
auto operator*(const SEnExpression<Expr>& lhs,
               const Eigen::MatrixBase<Derived>& rhs) {
    // TODO Support allowing multiple vectors to be stacked horizontally in rhs?
    EIGEN_STATIC_ASSERT_VECTOR_ONLY(Derived);
    const Expr& lhs_expr = static_cast<const Expr&>(lhs);
    return lhs_expr.rotation() * rhs + lhs_expr.translation();
}

}  // namespace detail
}  // namespace liegr
