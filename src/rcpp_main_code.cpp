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
  
  // These have to be shared_ptr per Thrift interface
  auto socket = make_shared<TSocket>(host, port);
  auto transport = make_shared<TBufferedTransport>(socket);
  auto protocol = make_shared<TBinaryProtocol>(transport);
  MapDClient* client = new MapDClient(protocol);  //new required to avoid falling out of scope
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
  
  //method to get session value from OmniSci
  client->connect(session, user_name, passwd, db_name);
  
  //bundle up info as pointers, return to R in List
  TTransport* tt = transport.get();  //needs raw, not shared_ptr
  XPtr<TTransport> ptt(tt, true);
  
  XPtr<MapDClient> pmdc(client, true);

  return List::create(_["transport"] = ptt,
                      _["client"]    = pmdc,
                      _["sessionId"] = session
                      );
  
}

// [[Rcpp::export]]
void disconnect(List conn){
  
  XPtr<MapDClient> client = conn["client"];
  string sessionId = conn["sessionId"];
  XPtr<TTransport> transport = conn["transport"];
  
  client->disconnect(sessionId);
  transport->close();
  
}

// [[Rcpp::export]]
List get_table_details(List conn, std::string table_name) {
  
  TTableDetails table_details;
  
  XPtr<MapDClient> client = conn["client"];
  string sessionId = conn["sessionId"];
  
  client->get_table_details(table_details, sessionId, table_name);
  
  //for debugging
  std::cout << table_details << std::endl;
  
  //parse table_details once code works
  //_["partition_detail"] = table_details.partition_detail
  //_["row_desc"] = table_details.row_desc
  return List::create(_["fragment_size"] = table_details.fragment_size,
                      _["page_size"] = table_details.page_size,
                      _["max_rows"] = table_details.max_rows,
                      _["view_sql"] = table_details.view_sql,
                      _["shard_count"] = table_details.shard_count,
                      _["key_metainfo"] = table_details.key_metainfo,
                      _["is_temporary"] = table_details.is_temporary);
  
}