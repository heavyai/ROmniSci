test_that("Connect to OmniSci on localhost and get session info", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  gsi <- get_session_info(conn)

  expect_true(gsi$user == "mapd")

})
