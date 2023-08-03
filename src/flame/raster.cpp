#include "flame/bits/raster.hpp"

namespace flame {

/**
 * Raster base class.
 * Used as a PIMPL in main flame::raster struct.
 */
class raster::raster_base
{

  private:
    af::array data_;
};

} // namespace flame
