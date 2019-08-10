test_that("Connect to OmniSci on localhost and get tables meta", {
  
  conn <- connect("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gtm <- get_tables_meta(conn)

  expect_true(length(gtm) >= 1)

})
