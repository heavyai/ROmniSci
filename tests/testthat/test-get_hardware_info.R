test_that("Connect to OmniSci on localhost and get hardware info", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  ghi <- get_hardware_info(conn)

  expect_true(length(ghi)>= 1)

})
