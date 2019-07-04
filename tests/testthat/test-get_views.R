test_that("Connect to OmniSci on localhost and get views in database", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  gvs <- get_views(conn)

  expect_true(length(gvs)>= 0)

})
