#DBItest::make_context(OmniSci(), NULL)
#DBItest::test_all()
# DBItest::test_compliance(skip = NULL, 
#                               run_only = NULL, 
#                               ctx = DBItest::get_default_context())

test_that("Connect to OmniSci using dbConnect", {
  
  conn <- dbConnect(ROmniSci::OmniSci())
  
  expect_true(class(conn@thriftconn$transport) == "externalptr")
  expect_true(class(conn@thriftconn$client) == "externalptr")
  expect_true(class(conn@thriftconn$sessionid) == "character")
  
})