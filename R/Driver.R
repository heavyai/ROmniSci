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

#' @rdname DBI
#' @inheritParams DBI::dbGetInfo
#' @export
setMethod(
  "dbGetInfo", "OmniSciDriver",
  function(dbObj, ...) {
    
    #Unclear what this is supposed to represent
    #Returning package name and version until it becomes more clear
    return(list(name = utils::packageName(), 
                version = utils::packageVersion(utils::packageName()))
           )
    
})

#' @rdname DBI
#' @inheritParams DBI::dbIsValid
#' @export
setMethod(
  "dbIsValid", "OmniSciDriver",
  function(dbObj, ...) {
    TRUE  # this is true by definition
})