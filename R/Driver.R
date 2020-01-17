#' @include ROmniSci.R
NULL

#' OmniSci driver
#'
#' Formal class OmniSciDriver
#'
#' @export
#' @import methods DBI
#' @examples
#' library(DBI)
#' ROmniSci::OmniSci()
OmniSci <- function() {
  new("OmniSciDriver")
}

#' @rdname DBI
#' @export
setClass("OmniSciDriver", contains = "DBIDriver")

#' @rdname DBI
#' @export
setMethod("dbUnloadDriver", "OmniSciDriver", function(drv, ...) {
  NULL  #set as a no-op
})

#' @rdname DBI
#' @inheritParams methods::show
#' @export
setMethod(
  "show", "OmniSciDriver",
  function(object) {
    cat("<OmniSciDriver>\n")
})







#### Not implemented yet

#' @rdname DBI
#' @inheritParams DBI::dbDataType
#' @export
setMethod(
  "dbDataType", "OmniSciDriver",
  function(dbObj, obj, ...) {
    # Optional: Can remove this if all data types conform to SQL-92
    tryCatch(
      getMethod("dbDataType", "DBIObject", asNamespace("DBI"))(dbObj, obj, ...),
      error = function(e) testthat::skip("Not yet implemented: dbDataType(Driver)"))
  })

#' @rdname DBI
#' @inheritParams DBI::dbDataType
#' @export
setMethod(
  "dbDataType", c("OmniSciDriver", "list"),
  function(dbObj, obj, ...) {
    # rstats-db/DBI#70
    testthat::skip("Not yet implemented: dbDataType(Driver, list)")
  })

#' @rdname DBI
#' @inheritParams DBI::dbIsValid
#' @export
setMethod(
  "dbIsValid", "OmniSciDriver",
  function(dbObj, ...) {
    testthat::skip("Not yet implemented: dbIsValid(Driver)")
  })

#' @rdname DBI
#' @inheritParams DBI::dbGetInfo
#' @export
setMethod(
  "dbGetInfo", "OmniSciDriver",
  function(dbObj, ...) {
    testthat::skip("Not yet implemented: dbGetInfo(Driver)")
  })