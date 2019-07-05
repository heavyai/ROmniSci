#include "MapD.h" 

namespace Rcpp {

  //enums
  // template <> SEXP wrap(const TPartitionDetail& tpd);
  // template <> SEXP wrap(const TDatumType& tdt);
  // template <> SEXP wrap(const TEncodingType& tet);
  
  //structs
  template <> SEXP wrap(const TTypeInfo& x);
  template <> SEXP wrap(const TTableDetails& x);
  template <> SEXP wrap(const TColumnType& x);
  template <> SEXP wrap(const TServerStatus& x);
  template <> SEXP wrap(const TSessionInfo& x);
  template <> SEXP wrap(const TDBInfo& x);
  template <> SEXP wrap(const TClusterHardwareInfo& x);
  template <> SEXP wrap(const THardwareInfo& x);
  template <> SEXP wrap(const TGpuSpecification& x);

}
