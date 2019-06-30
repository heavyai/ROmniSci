#include "MapD.h" // TODO: will this cause problems being included twice? here, and where
                  // included in current rcpp_main_code.cpp?

namespace Rcpp {

  //TODO: can I loop over this to substitute in references? all return SEXP, all named wrap
  template <> SEXP wrap(const TTypeInfo& tti);
  template <> SEXP wrap(const TTableDetails& ttd);
  template <> SEXP wrap(const TColumnType& tct);

}
