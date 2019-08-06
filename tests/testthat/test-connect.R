test_that("Connect to OmniSci on localhost and defaults", {
  
  conn <- connect("localhost", 6274, "admin", "HyperInteractive", "omnisci")
  
  expect_true(class(conn$transport) == "externalptr")
  expect_true(class(conn$client) == "externalptr")
  expect_true(class(conn$sessionid) == "character")

})

