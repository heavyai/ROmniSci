test_that("Connect to OmniSci on localhost and defaults", {
  
  conn <- connect("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  ttd <- get_table_details(conn, "omnisci_states")

  expect_equal(length(ttd), 9)

})

