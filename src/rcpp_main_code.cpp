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


//forward declarations have to come before '#include <Rcpp.h>'
#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
List connect(std::string host, int port, std::string user_name, std::string passwd, std::string db_name){
  
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
  
  //bundle up info as pointers, return to R in List
  TTransport* tt = transport.get();  //needs raw, not shared_ptr
  XPtr<TTransport> ptt(tt, true);
  
  MapDClient* mdc = &client;
  XPtr<MapDClient> pmdc(mdc, true);

  return List::create(_["transport"] = ptt,
                      _["client"]    = pmdc,
                      _["sessionId"] = session
                      );
  
}

// [[Rcpp::export]]
List get_table_details(List conn, std::string table_name) {
  
  TTableDetails table_details;
  
  //Q1: how do I get value of type MapDClient back from conn?
  //this code bombs out R session
  XPtr<MapDClient> client = conn["client"];  //generic_name_proxy<19, PreserveStorage> to XPtr
  string sessionId = conn["sessionId"];
  
  client->get_table_details(table_details, sessionId, table_name);
  
  //for debugging
  std::cout << table_details << std::endl;
  
  //parse table_details once code works
  return List::create(_["transport"] = sessionId);
  
}