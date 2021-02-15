#pragma once

namespace liegr {
namespace detail {

template <typename E>
class GroupExpression {
   public:
    auto matrix() const { return static_cast<const E&>(*this).matrix(); }
};

template <typename E1, typename E2>
class GroupMultiply : public GroupExpression<GroupMultiply<E1, E2>> {
   public:
    GroupMultiply(const E1& lhs, const E2& rhs) : lhs_(lhs), rhs_(rhs) {}

    auto matrix() const { return lhs_.matrix() * rhs_.matrix(); }

   private:
    const E1& lhs_;
    const E2& rhs_;
};

template <typename E1, typename E2>
GroupMultiply<E1, E2> operator*(const GroupExpression<E1>& lhs,
                                const GroupExpression<E2>& rhs) {
    return GroupMultiply<E1, E2>(static_cast<const E1&>(lhs),
                                 static_cast<const E2&>(rhs));
}

}  // namespace detail
}  // namespace liegr
