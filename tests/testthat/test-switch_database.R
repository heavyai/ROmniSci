test_that("Connect to OmniSci on localhost, create, then switch database", {
  
  conn <- connect_binary("0.0.0.0", 6274, "admin", "HyperInteractive", "omnisci")
  
  sql_execute(conn, "create database if not exists romnisci (owner='admin')")
  expect_error(switch_database(conn, "romnisci"), NA)
  
  #clean up after 
  sql_execute(conn, "drop database if exists romnisci")

})
