#' Driver for OmniSci database.
#' 
#' @keywords internal
#' @export
#' @import DBI
#' @import methods
setClass("OmniSciDriver", contains = "DBIDriver")

#' @export
#' @rdname OmniSci-class
setMethod("dbUnloadDriver", "OmniSciDriver", function(drv, ...) {
  TRUE
})

setMethod("show", "OmniSciDriver", function(object) {
  cat("<OmniSciDriver>\n")
})

#' @export
OmniSci <- function() {
  new("OmniSciDriver")
}