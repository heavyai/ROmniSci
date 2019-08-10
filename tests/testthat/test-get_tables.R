test_that("Connect to OmniSci on localhost and get tables in database", {
  
  conn <- connect("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gt <- get_tables(conn)

  # This doesn't have to be strictly true for all databases, but will hold
  # on a stock Docker container
  expect_true(length(gt) > 0)

})
