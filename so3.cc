#include "so3.hh"

namespace liegr {

SO3 SO3::Exp(const TangentVector& x) {}

SO3::TangentVector SO3::Log() const {}

// SO3 SO3::inverse() const { return SO3(matrix_.transpose()); }

SO3 SO3::random() { return Exp(TangentVector::Random()); }

}  // namespace liegr
