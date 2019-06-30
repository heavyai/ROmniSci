#include "MapD.h" // will this cause problems being included twice? here, and where
                  // included in current rcpp_main_code.cpp?

namespace Rcpp {

  template <> SEXP wrap(const TTypeInfo& tti);
  template <> SEXP wrap(const TTableDetails& ttd);
  template <> SEXP wrap(const TColumnType& tct);

}
