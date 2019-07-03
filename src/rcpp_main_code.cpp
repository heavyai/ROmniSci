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

//' Connect to an OmniSci database
//' 
//' @param host host
//' @param port port
//' @param username username
//' @param passwd passwd
//' @param db_name db_name
//' 
//'
//' 
//'
//' @export
// [[Rcpp::export]]
List connect(std::string host, 
             int port, 
             std::string username, 
             std::string passwd, 
             std::string db_name){
  
  auto socket = std::make_shared<TSocket>(host, port);
  auto transport = std::make_shared<TBufferedTransport>(socket);
  auto pcol = std::make_shared<TBinaryProtocol>(transport);
  MapDClient* client = new MapDClient(pcol);  //new required to avoid falling out of scope
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
  
  //get session value from OmniSci
  client->connect(session, username, passwd, db_name);
  
  //bundle up info as pointers, return to R in List
  //Per Matt Pulver, is this scoped right or am I getting lucky?
  TTransport* tt = transport.get();  //needs raw, not shared_ptr
  XPtr<TTransport> ptt(tt, true);
  
  XPtr<MapDClient> pmdc(client, true);
  
  return List::create(_["transport"] = ptt,
                      _["client"]    = pmdc,
                      _["sessionId"] = session
  );
  
}

//' Disconnect from an OmniSci database
//'
//' @param conn conn
//'
//' @export
// [[Rcpp::export]]
void disconnect(List conn){
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  XPtr<TTransport> transport = conn["transport"];
  
  client->disconnect(sessionid);
  transport->close();
  
}
  
//' Get details of the specified database table
//'
//' @param conn conn
//' @param table_name table_name
//'
//' @export
// [[Rcpp::export]]
List get_table_details(List conn, std::string table_name) {
  
  TTableDetails table_details;
  
  XPtr<MapDClient> client = conn["client"];
  std::string sessionid = conn["sessionid"];
  
  client->get_table_details(table_details, sessionid, table_name);

  return(Rcpp::wrap(table_details));
}