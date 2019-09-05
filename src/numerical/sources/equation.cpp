#include "equation.hpp"

namespace num
{

EquaDiff::EquaDiff(DiffFct fct, double init_value, double threshold)
    : diff_fct(fct)
    , init_value(init_value)
    , threshold(threshold)
    {}

} // namespace num

