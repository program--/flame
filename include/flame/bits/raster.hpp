#pragma once

#include <memory>

#include <arrayfire.h>

namespace flame {

enum class iterate : unsigned
{
    rows    = 0,
    columns = 1,
    cells   = 2
};

struct raster
{
  private:
    class raster_base;

    /// Pointer to implementation
    std::unique_ptr<raster_base> ptr_;

  public:
    struct cell;
    struct view;
    struct iterator;

    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using extent_type     = std::tuple<double, double, double, double>;

    // ------------------------------------------------------------------------
    // Public Interface -------------------------------------------------------
    // ------------------------------------------------------------------------

    /* === Access ========================================================== */

    /**
     * @brief Access the cell at the given index.
     * @note Performs a bounds check.
     * @param row Row index.
     * @param column Column index.
     * @return cell Cell pointing to the given row/column indices.
     */
    cell at(size_type row, size_type column);

    /**
     * @brief Access the cell at the given index.
     * @note Does not perform a bounds check.
     * @param n Row/column pair
     * @return cell Cell pointing to the given row/column indices.
     */
    cell operator[](std::pair<size_type, size_type> n);

    /**
     * @brief Access a view of the row at the given index.
     * @param n Row index.
     * @return view
     */
    view row(size_type n);

    /**
     * @brief Access a view of the column at the given index.
     * @param n Column index.
     * @return view
     */
    view column(size_type n);

    /**
     * @brief Returns a beginning iterator based
     *        on the raster's iteration mode.
     * @return iterator
     */
    iterator begin();

    /**
     * @brief Returns an end iterator based
     *        on the raster's iteration mode.
     * @return iterator
     */
    iterator end();

    /* === Metadata ======================================================== */

    /**
     * @brief Get the number of columns.
     * @return size_type Number of columns.
     */
    size_type ncol() const noexcept;

    /**
     * @brief Get the number of rows.
     * @return size_type Number of rows.
     */
    size_type nrow() const noexcept;

    /**
     * @brief Get the number of cells.
     * @return size_type Number of cells.
     */
    size_type ncell() const noexcept;

    /**
     * @brief Get the geographic extent.
     * @return extent_type
     */
    extent_type extent() const noexcept;

    /* === Actions ========================================================= */

    /**
     * Static cast this raster.
     *
     * @tparam To Type to cast raster to.
     */
    template<typename To>
    void cast();

    /**
     * Runtime case this raster.
     *
     * @param type Type info used to determine cast.
     * @example
     * @code{cpp}
     * auto some_var = ...;
     * raster my_raster;
     *
     * ...
     *
     * my_raster.cast(typeid(some_var));
     * // OR
     * my_raster.cast(typeid(int));
     * @endcode
     */
    void cast(const std::type_info& type);

    /**
     * @brief Retrieve a reference to this raster's iteration mode.
     *        This can be set to one of: rows, columns, or cells.
     * @return iterate&
     */
    iterate& iterate_mode() noexcept;

    /**
     * Apply a function to the cells of this raster.
     *
     * @note Modifies in place.
     *
     * @tparam Functor
     * @param f Function or Lambda
     * @return raster&
     */
    template<typename Functor>
    raster& apply(Functor f);

    template<typename T>
    raster& operator+=(T n);

    template<typename T>
    raster& operator-=(T n);

    template<typename T>
    raster& operator*=(T n);

    template<typename T>
    raster& operator/=(T n);
}; // class raster

} // namespace flame
