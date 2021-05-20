#pragma once

#include "detail/expression.hh"

#include <eigen3/Eigen/Core>

namespace liegr {

class SO3 : public detail::SOnExpression<SO3> {
   public:
    using MatrixType = Eigen::Matrix3d;

    static constexpr size_t DOF = 3;
    static constexpr size_t DIM = 3;

    using TangentVector = Eigen::Matrix<double, DOF, 1>;
    using TangentMapping = Eigen::Matrix<double, DOF, DOF>;
    using ActionVector = Eigen::Matrix<double, DIM, 1>;

    // Constructors
    SO3() { matrix_.setIdentity(); }

    template <typename Expr>
    SO3(const detail::SOnExpression<Expr>& expr) : matrix_(expr.matrix()) {}

    // Methods
    static SO3 identity() { return SO3(); }
    static SO3 Exp(const TangentVector& x);
    TangentVector Log() const;

    static SO3 random();

    // Access underlying matrix representation
    const MatrixType& matrix() const { return matrix_; }

   private:
    SO3(const MatrixType& matrix) : matrix_(matrix) {}

    MatrixType matrix_;
};

}  // namespace liegr
