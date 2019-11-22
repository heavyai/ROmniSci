test_that("Disconnect from OmniSci on localhost and defaults", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  disconnect(conn)
  
  # When disconnect called, no return from function
  # If you try to call a function after disconnect, you get a TTransportException
  # because socket gets closed
  expect_error(get_table_details(conn, "omnisci_states"),
               class = "apache::thrift::transport::TTransportException")

})

