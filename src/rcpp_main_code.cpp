#include <RcppCommon.h>
#include <iostream>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "MapD.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using std::make_shared;
using std::string;

struct Connection{
  
  std::shared_ptr<TTransport> transport; //needed to close socket
  MapDClient client;  //functions come from this class
  TSessionId sessionId; //this is a typedef alias to string
  
};

//forward declarations have to come before '#include <Rcpp.h>'
#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
SEXP connect_binary(const std::string& host, int& port, const std::string& user_name, const std::string& passwd, const std::string& db_name){
  
  // These have to be shared, all Thrift interface supports
  auto socket = make_shared<TSocket>(host, port);
  auto transport = make_shared<TBufferedTransport>(socket);
  auto protocol = make_shared<TBinaryProtocol>(transport);
  MapDClient client = MapDClient(protocol);
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
  
  //method to get session value from OmniSci
  client.connect(session, user_name, passwd, db_name);
  
  //bundle up info into Connection struct, return pointer to R
  auto c = Connection{transport, client, session};
  Connection* cptr = &c;
  XPtr<Connection> p(cptr, true);
  return(p);
  
}

// [[Rcpp::export]]
List get_table_details(SEXP conn, std::string table_name) {
  
  TTableDetails table_details;
  
  //Q1: how do I get back the Connection value from SEXP conn?
  //this compiles, but bombs out RStudio/R session
  
  Rcpp::XPtr<Connection> pConnection(conn);
  auto client = pConnection->client;
  auto sessionId = pConnection->sessionId;
  client.get_table_details(table_details, sessionId, table_name);
  
  //parse table_details once code works
  return List::create(_["transport"] = sessionId);
  
}