#pragma once

namespace liegr {
namespace detail {

template <typename Expr>
class GroupExpression {
   public:
    auto matrix() const { return static_cast<const Expr&>(*this).matrix(); }
};

template <typename LhsExpr, typename RhsExpr>
class GroupMultiply : public GroupExpression<GroupMultiply<LhsExpr, RhsExpr>> {
   public:
    GroupMultiply(const LhsExpr& lhs, const RhsExpr& rhs)
        : lhs_(lhs), rhs_(rhs) {}

    auto matrix() const { return lhs_.matrix() * rhs_.matrix(); }

   private:
    const LhsExpr& lhs_;
    const RhsExpr& rhs_;
};

template <typename LhsExpr, typename RhsExpr>
GroupMultiply<LhsExpr, RhsExpr> operator*(const GroupExpression<LhsExpr>& lhs,
                                          const GroupExpression<RhsExpr>& rhs) {
    return GroupMultiply<LhsExpr, RhsExpr>(static_cast<const LhsExpr&>(lhs),
                                           static_cast<const RhsExpr&>(rhs));
}

}  // namespace detail
}  // namespace liegr
