#include "flame/raster.hpp"

namespace flame {
namespace detail {

template<>
raster_base<float>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::f32){};

template<>
raster_base<double>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::f64){};

template<>
raster_base<short>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::s16){};

template<>
raster_base<int>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::s32){};

template<>
raster_base<long>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::s64){};

template<>
raster_base<unsigned short>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::u16){};

template<>
raster_base<unsigned int>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::u32){};

template<>
raster_base<unsigned long>::raster_base(size_type columns, size_type rows)
  : m_data(columns, rows, af::dtype::u64){};

} // namespace detail
} // namespace flame