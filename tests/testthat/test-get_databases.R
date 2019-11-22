test_that("Connect to OmniSci on localhost and get databases", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gdb <- get_databases(conn)

  expect_true(length(gdb) >= 1)

})
