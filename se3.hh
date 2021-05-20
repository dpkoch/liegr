#pragma once

#include <eigen3/Eigen/Core>

#include "detail/expression.hh"
#include "so3.hh"

namespace liegr {

class SE3 : public detail::SEnExpression<SE3> {
   public:
    using RotationType = SO3;
    using TranslationType = Eigen::Vector3d;

    static constexpr size_t DOF = 6;
    static constexpr size_t DIM = 3;

    using TangentVector = Eigen::Matrix<double, DOF, 1>;
    using TangentMapping = Eigen::Matrix<double, DOF, DOF>;
    using ActionVector = Eigen::Matrix<double, DIM, 1>;

    // Constructors
    SE3() { translation_.setZero(); }

    template <typename Expr>
    SE3(const detail::SEnExpression<Expr>& expr)
        : rotation_(expr.rotation()), translation_(expr.translation()) {}

    // Methods
    static SE3 identity() { return SE3(); }
    static SE3 Exp(const TangentVector& x);
    TangentVector Log() const;

    static SE3 random();

    // Access underlying data representations
    const RotationType& rotation() const { return rotation_; }
    const TranslationType& translation() const { return translation_; }

   private:
    SE3(const RotationType& rotation, const TranslationType& translation)
        : rotation_(rotation), translation_(translation) {}

    RotationType rotation_;
    TranslationType translation_;
};

}  // namespace liegr
