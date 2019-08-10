test_that("Connect to OmniSci on localhost and get hardware info", {
  
  conn <- connect("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  ghi <- get_hardware_info(conn)

  expect_true(length(ghi) >= 1)

})
