test_that("Connect to OmniSci on localhost and get session info", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  gsi <- get_session_info(conn)

  expect_true(gsi$user == "admin")

})
