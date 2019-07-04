#include <RcppCommon.h> // has to be before forward declarations
#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "MapD.h"
#include "rcpp_wrap.h" //forward declarations have to come before '#include <Rcpp.h>'
#include <Rcpp.h>

using namespace Rcpp;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

//' @title Connect to an OmniSci database
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @param host host
//' @param port port
//' @param username username
//' @param password password
//' @param dbname dbname
//' 
//' @return List
//' @export
//' @examples
//' \dontrun{
//'   
//'   conn <- connect("localhost", 6274, "admin", "HyperInteractive", "omnisci")
//'   
//' }
// [[Rcpp::export]]
List connect(std::string host, 
             int port, 
             std::string username, 
             std::string password, 
             std::string dbname){
  
  auto socket = std::make_shared<TSocket>(host, port);
  auto transport = std::make_shared<TBufferedTransport>(socket);
  auto pcol = std::make_shared<TBinaryProtocol>(transport);
  MapDClient* client = new MapDClient(pcol);  //new required to avoid falling out of scope
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
  
  //get session value from OmniSci
  client->connect(session, username, password, dbname);
  
  //bundle up info as pointers, return to R in List
  //Per Matt Pulver, is this scoped right or am I getting lucky?
  TTransport* tt = transport.get();  //needs raw, not shared_ptr
  XPtr<TTransport> ptt(tt, true);
  
  XPtr<MapDClient> pmdc(client, true);
  
  return List::create(_["transport"] = ptt,
                      _["client"]    = pmdc,
                      _["sessionid"] = session
  );
  
}

//' @title Disconnect from an OmniSci database
//'
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return Nothing
//' @export
//' @examples
//' \dontrun{
//'   
//'   disconnect(conn)
//'   
//' }
// [[Rcpp::export]]
void disconnect(List conn){
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  XPtr<TTransport> transport = conn["transport"];
  
  client->disconnect(sessionid);
  transport->close();
  
}
  
//' @title Get details of the specified database table
//'
//' @param conn conn
//' @param table_name table_name
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List (TTableDetails)
//' @export
//' @examples
//' \dontrun{
//' 
//' tbl_details <- get_table_details(conn, "omnisci_states")
//' 
//' } 
// [[Rcpp::export]]
List get_table_details(List conn, std::string table_name) {
  
  TTableDetails table_details;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_table_details(table_details, sessionid, table_name);

  return(Rcpp::wrap(table_details));
}


//' @title Get status of OmniSci server
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List (TServerStatus)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gss <- get_server_status(conn)
//' 
//' } 
// [[Rcpp::export]]
List get_server_status(List conn){
  
  TServerStatus tss;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_server_status(tss, sessionid);
  
  return(Rcpp::wrap(tss));  
  
}

//' @title Get status of OmniSci server
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List (TServerStatus)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gs <- get_status(conn)
//' 
//' } 
// [[Rcpp::export]]
List get_status(List conn){
  
  std::vector<TServerStatus> tss;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_status(tss, sessionid);
  
  for(auto x: tss){
    tss.push_back(x);
  }

  return(Rcpp::wrap(tss));  
  
}

//' @title Get version of OmniSci server
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return Character
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gv <- get_version(conn)
//' 
//' } 
// [[Rcpp::export]]
CharacterVector get_version(List conn){
  
  std::string gv;
  
  XPtr<MapDClient> client = conn["client"];

  client->get_version(gv);
  
  return(gv);  
  
}

//' @title Get tables in current database
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List(Character)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gt <- get_tables(conn)
//' 
//' } 
// [[Rcpp::export]]
CharacterVector get_tables(List conn){
  
  std::vector<std::string> tables;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_tables(tables, sessionid);
  
  return(Rcpp::wrap(tables));  
  
}

//' @title Get users in current database
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List(Character)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gu <- get_users(conn)
//' 
//' } 
// [[Rcpp::export]]
CharacterVector get_users(List conn){
  
  std::vector<std::string> users;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_users(users, sessionid);
  
  return(Rcpp::wrap(users));  
  
}

//' @title Get physical tables in current database
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List(Character)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gpt <- get_physical_tables(conn)
//' 
//' } 
// [[Rcpp::export]]
CharacterVector get_physical_tables(List conn){
  
  std::vector<std::string> tables;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_physical_tables(tables, sessionid);
  
  return(Rcpp::wrap(tables));
  
}

//' @title Get views in current database
//' 
//' @param conn conn
//' 
//' @details TBD Details
//' 
//' @description TBD description
//' 
//' @return List(Character)
//' 
//' @export
//' @examples
//' \dontrun{
//' 
//' gvs <- get_views(conn)
//' 
//' } 
// [[Rcpp::export]]
CharacterVector get_views(List conn){
  
  std::vector<std::string> views;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_views(views, sessionid);
  
  return(Rcpp::wrap(views));
  
}