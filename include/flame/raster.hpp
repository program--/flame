#pragma once
#include <af/half.h>
#include <arrayfire.h>
#include <functional>
#include <type_traits>

#define FLAME_CPP_TO_AF(cpp_t, af_dtype)                     \
    template<>                                               \
    constexpr af::dtype raster_base<cpp_t>::dtype() noexcept \
    {                                                        \
        return af_dtype;                                     \
    }

namespace flame {

using half = af::half;

namespace traits {

template<typename F, typename... Args>
struct is_invocable
  : std::is_constructible<
      std::function<void(Args...)>,
      std::reference_wrapper<typename std::remove_reference<F>::type>>
{};

} // namespace traits
namespace detail {

struct extent
{
    double xmin;
    double ymin;
    double xmax;
    double ymax;
};

template<
  typename T,
  std::enable_if_t<
    std::is_arithmetic<T>::value || std::is_same<T, half>::value,
    bool> = true>
struct raster_base
{
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using extent_type     = extent;

    struct cell;
    struct view;

    raster_base(size_type columns, size_type rows)
      : m_data(columns, rows, raster_base::dtype()){};

    raster_base(
      size_type                      columns,
      size_type                      rows,
      const std::vector<value_type>& values
    )
      : m_data(columns, rows, values.data()){};

    // Building
    raster_base& with_extent(extent_type extent);
    raster_base& with_crs(size_type srid);

    // Info
    size_type ncol() const noexcept;
    size_type nrow() const noexcept;
    size_type ncell() const noexcept;
    double    xmin() const noexcept;
    double    xmax() const noexcept;
    double    ymin() const noexcept;
    double    ymax() const noexcept;

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

    // Mutate
    template<
      typename Function,
      std::enable_if_t<
        traits::is_invocable<Function, value_type>::value,
        bool> = true>
    raster_base& apply(Function f);

  private:
    static constexpr af::dtype dtype() noexcept;

    af::array                  m_data;
    extent_type                m_extent;
    size_type                  m_srid;
};

FLAME_CPP_TO_AF(half, af::dtype::f16);
FLAME_CPP_TO_AF(float, af::dtype::f32);
FLAME_CPP_TO_AF(double, af::dtype::f64);
FLAME_CPP_TO_AF(short, af::dtype::s16);
FLAME_CPP_TO_AF(int, af::dtype::s32);
FLAME_CPP_TO_AF(long, af::dtype::s64);
FLAME_CPP_TO_AF(unsigned short, af::dtype::u16);
FLAME_CPP_TO_AF(unsigned int, af::dtype::u32);
FLAME_CPP_TO_AF(unsigned long, af::dtype::u64);

} // namespace detail

using raster_f64 = detail::raster_base<double>;
using raster_f32 = detail::raster_base<float>;
using raster_f16 = detail::raster_base<af::half>;
using raster_i64 = detail::raster_base<long>;
using raster_i32 = detail::raster_base<int>;
using raster_i16 = detail::raster_base<short>;
using raster_u64 = detail::raster_base<unsigned long>;
using raster_u32 = detail::raster_base<unsigned int>;
using raster_u16 = detail::raster_base<unsigned short>;

// Typical numeric raster
using raster = detail::raster_base<double>;

} // namespace flame

#undef FLAME_CPP_TO_AF
