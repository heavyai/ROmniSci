test_that("Connect to OmniSci on localhost and get databases", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  gdb <- get_databases(conn)

  expect_true(length(gdb)>= 1)

})
