test_that("Connect to OmniSci on localhost and get server status", {
  
  conn <- connect("localhost", 6274, "admin", "HyperInteractive", "omnisci")
  gss <- get_server_status(conn)

  expect_equal(length(gss), 8)

})
