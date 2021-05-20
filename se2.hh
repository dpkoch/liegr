#pragma once

#include <eigen3/Eigen/Core>

#include "detail/expression.hh"
#include "so2.hh"

namespace liegr {

class SE2 : public detail::SEnExpression<SE2> {
   public:
    using RotationType = SO2;
    using TranslationType = Eigen::Vector2d;

    static constexpr size_t DOF = 3;
    static constexpr size_t DIM = 2;

    using TangentVector = Eigen::Matrix<double, DOF, 1>;
    using TangentMapping = Eigen::Matrix<double, DOF, DOF>;
    using ActionVector = Eigen::Matrix<double, DIM, 1>;

    // Constructors
    SE2() { translation_.setZero(); }

    template <typename Expr>
    SE2(const detail::SEnExpression<Expr>& expr)
        : rotation_(expr.rotation()), translation_(expr.translation()) {}

    // Methods
    static SE2 identity() { return SE2(); }
    static SE2 Exp(const TangentVector& x);
    TangentVector Log() const;

    static SE2 random();

    // Access underlying data representations
    const RotationType& rotation() const { return rotation_; }
    const TranslationType& translation() const { return translation_; }

   private:
    SE2(const RotationType& rotation, const TranslationType& translation)
        : rotation_(rotation), translation_(translation) {}

    RotationType rotation_;
    TranslationType translation_;
};

}  // namespace liegr
