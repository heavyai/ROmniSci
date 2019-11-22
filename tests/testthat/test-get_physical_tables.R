test_that("Connect to OmniSci on localhost and get physical tables in database", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gpt <- get_physical_tables(conn)

  # This doesn't have to be strictly true for all databases, but will hold
  # on a stock Docker container
  expect_true(length(gpt)> 0)

})
