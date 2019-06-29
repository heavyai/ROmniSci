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

namespace Rcpp {

    template <> SEXP wrap(const TTypeInfo& tti);
    template <> SEXP wrap(const TTableDetails& ttd);
    template <> SEXP wrap(const TColumnType& tct);

}


//forward declarations have to come before '#include <Rcpp.h>'
#include <Rcpp.h>
using namespace Rcpp;

//implementation of forward declarations has to come after '#include <Rcpp.h>'
namespace Rcpp {

  template <> SEXP wrap(const TTypeInfo& tti){

    return List::create(_["type"] = static_cast<int>(tti.type),  //enum
                        _["encoding"] = static_cast<int>(tti.encoding), //enum
                        _["nullable"] = tti.nullable,
                        _["is_array"] = tti.is_array,
                        _["precision"] = tti.precision,
                        _["scale"] = tti.scale,
                        _["comp_param"] = tti.comp_param,
                        _["size"] = tti.size
                       );
    
  };

  template <> SEXP wrap(const TColumnType& tct){
    
    return List::create(_["col_name"] = tct.col_name,
                        _["col_type"] = Rcpp::wrap(tct.col_type),
                        _["is_reserved_keyword"] = tct.is_reserved_keyword,
                        _["src_name"] = tct.src_name, 
                        _["is_system"] = tct.is_system,
                        _["is_physical"] = tct.is_physical,
                        _["col_id"] = tct.col_id
                       );
    
  };

  template <> SEXP wrap(const TTableDetails& ttd){
    
    //parse ttd.row_desc to SEXP using wrap defined above
    std::vector<SEXP> outvec;
    for(TColumnType x: ttd.row_desc) {
      outvec.push_back(Rcpp::wrap(x));
    }

    return List::create(_["fragment_size"] = ttd.fragment_size, 
                        _["page_size"] = static_cast<int>(ttd.page_size),
                        _["max_rows"] = ttd.max_rows,
                        _["view_sql"] = ttd.view_sql,
                        _["shard_count"] = static_cast<int>(ttd.shard_count),
                        _["key_metainfo"] = ttd.key_metainfo,
                        _["is_temporary"] = ttd.is_temporary,
                        _["partition_detail"] = static_cast<int>(ttd.partition_detail), //enum
                        _["row_desc"] = outvec
                       );
  
  };

} //end namespace


// [[Rcpp::export]]
List connect(std::string host, 
             int port, 
             std::string user_name, 
             std::string passwd, 
             std::string db_name){
  
  // These have to be shared_ptr per Thrift interface
  auto socket = make_shared<TSocket>(host, port);
  auto transport = make_shared<TBufferedTransport>(socket);
  auto pcol = make_shared<TBinaryProtocol>(transport);
  MapDClient* client = new MapDClient(pcol);  //new required to avoid falling out of scope
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
  
  //method to get session value from OmniSci
  client->connect(session, user_name, passwd, db_name);
  
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

  return(Rcpp::wrap(table_details));
}