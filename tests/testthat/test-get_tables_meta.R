test_that("Connect to OmniSci on localhost and get tables meta", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  gtm <- get_tables_meta(conn)

  expect_true(length(gtm)>= 1)

})
