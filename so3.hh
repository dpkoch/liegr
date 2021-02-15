#pragma once

#include "detail/expression.hh"

#include <eigen3/Eigen/Core>

namespace liegr {

class SO3 : public detail::GroupExpression<SO3> {
   public:
    using MatrixType = Eigen::Matrix3d;

    SO3() { matrix_.setIdentity(); }

    template <typename E>
    SO3(const detail::GroupExpression<E>& expr) : matrix_(expr.matrix()) {}

    const MatrixType& matrix() const { return matrix_; }

   private:
    MatrixType matrix_;
};

}  // namespace liegr
