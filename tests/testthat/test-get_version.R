test_that("Connect to OmniSci on localhost and get version", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gv <- get_version(conn)

  expect_true(nchar(gv) > 0)

})
