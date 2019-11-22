test_that("Connect to OmniSci on localhost and get views in database", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gvs <- get_views(conn)

  expect_true(length(gvs) >= 0)

})
