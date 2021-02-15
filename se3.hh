#pragma once

#include <eigen3/Eigen/Core>

#include "detail/expression.hh"
#include "so3.hh"

namespace liegr {

class SE3 : public detail::SEnExpression<SE3> {
   public:
    using RotationType = SO3;
    using TranslationType = Eigen::Vector3d;

    SE3() { translation_.setZero(); }

    template <typename Expr>
    SE3(const detail::SEnExpression<Expr>& expr)
        : rotation_(expr.rotation()), translation_(expr.translation()) {}

    const RotationType& rotation() const { return rotation_; }
    const TranslationType& translation() const { return translation_; }

   private:
    RotationType rotation_;
    TranslationType translation_;
};

}  // namespace liegr
