#pragma once

#include "detail/expression.hh"

#include <eigen3/Eigen/Core>

namespace liegr {

class SO2 : public detail::SOnExpression<SO2> {
   public:
    using MatrixType = Eigen::Matrix2d;

    SO2() { matrix_.setIdentity(); }

    template <typename Expr>
    SO2(const detail::SOnExpression<Expr>& expr) : matrix_(expr.matrix()) {}

    const MatrixType& matrix() const { return matrix_; }

   private:
    MatrixType matrix_;
};

}  // namespace liegr
