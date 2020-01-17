#DBItest::make_context(OmniSci(), NULL)
#DBItest::test_all()
# DBItest::test_compliance(skip = NULL, 
#                               run_only = NULL, 
#                               ctx = DBItest::get_default_context())

test_that("DBI Interface functions work", {
  
  #dbConnect
  conn <- dbConnect(ROmniSci::OmniSci())
  
  expect_true(class(conn@thriftconn$transport) == "externalptr")
  expect_true(class(conn@thriftconn$client) == "externalptr")
  expect_true(class(conn@thriftconn$sessionid) == "character")
  
  #dbGetInfo
  info1 <- dbGetInfo(ROmniSci::OmniSci())
  info2 <- dbGetInfo(conn)
  
  expect_true(info1$name == "ROmniSci")
  expect_named(info2, c("user", "database", "start_time", "hardware_info"))
  
})