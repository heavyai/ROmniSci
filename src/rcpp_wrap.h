#include "MapD.h" // TODO: will this cause problems being included twice? here, and where
                  // included in current rcpp_main_code.cpp?

namespace Rcpp {
  //TODO: can I loop over this to substitute in references? all return SEXP, all named wrap

  //enums
  // template <> SEXP wrap(const TPartitionDetail& tpd);
  // template <> SEXP wrap(const TDatumType& tdt);
  // template <> SEXP wrap(const TEncodingType& tet);
  
  //structs
  template <> SEXP wrap(const TTypeInfo& tti);
  template <> SEXP wrap(const TTableDetails& ttd);
  template <> SEXP wrap(const TColumnType& tct);
  template <> SEXP wrap(const TServerStatus& tss);
  

}
