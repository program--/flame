#pragma once
#include <arrayfire.h>

namespace flame {
namespace detail {

struct extent
{
    double xmin;
    double ymin;
    double xmax;
    double ymax;
};

template<typename T>
struct raster_base
{
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using extent_type     = extent;

    struct cell;
    struct view;

    raster_base(size_type columns, size_type rows);

    raster_base&                    with_extent(extent_type extent);
    raster_base&                    with_crs(size_type srid);
    size_type                       size() const noexcept;
    std::pair<size_type, size_type> shape() const noexcept;

    // Mathematical Operators
    raster_base& operator+(value_type n);
    raster_base& operator-(value_type n);
    raster_base& operator*(value_type n);
    raster_base& operator/(value_type n);

    // Access
    cell& at(size_type column, size_type row);
    cell& operator[](std::pair<size_type, size_type> index);

    view& row(size_type n);
    view& column(size_type n);
    view& operator[](size_type n);

  private:
    af::array   m_data;
    extent_type m_extent;
    size_type   m_srid;
};

} // namespace detail

using raster = detail::raster_base<double>;

} // namespace flame