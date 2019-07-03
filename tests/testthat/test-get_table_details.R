test_that("Connect to OmniSci on localhost and defaults", {
  
  conn <- connect("localhost", 6274, "mapd", "HyperInteractive", "mapd")
  ttd <- get_table_details(conn, "omnisci_states")

  expect_equal(length(ttd), 9)

})

