#include <Rcpp.h>

//https://gallery.rcpp.org/articles/creating-integer64-and-nanotime-vectors/
Rcpp::NumericVector makeInt64(int64_t v) {
  Rcpp::NumericVector n(1);         // storage vehicle we return them in
  
  // transfers values 'keeping bits' but changing type
  // using reinterpret_cast would get us a warning
  std::memcpy(&(n[0]), &(v), sizeof(double));
  
  n.attr("class") = "integer64";
  return n;
}

Rcpp::NumericVector makeInt64(std::vector<int64_t> v) {
  size_t len = v.size();
  Rcpp::NumericVector n(len);         // storage vehicle we return them in
  
  // transfers values 'keeping bits' but changing type
  // using reinterpret_cast would get us a warning
  std::memcpy(&(n[0]), &(v[0]), len * sizeof(double));
  
  n.attr("class") = "integer64";
  return n;
}