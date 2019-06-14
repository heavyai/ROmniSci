#include <Rcpp.h>
#include <iostream>
#include <string>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include "MapD.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using std::make_shared;
using std::string;

using namespace Rcpp;

//TODO: how do we make this into an R object (S3?) Connection
struct Connection{
  
  std::shared_ptr<TBufferedTransport> transport;
  MapDClient client;
  TSessionId sessionId;
  
};

// TODO: figure out how to return TTableDetails into an R object, then export function
TTableDetails get_table_details(MapDClient client, const TSessionId& session, const string& table_name) {
  
  TTableDetails table_details;
  
  client.get_table_details(table_details, session, table_name);
  
  return(table_details);
  
}

// Remove the first set of comment slashes to see error when trying to export 
// connect() into R
// // [[Rcpp::export]]
Connection connect(std::string host, int port, const std::string& user_name, const std::string& passwd, const std::string& db_name){
  
  auto socket {make_shared<TSocket>(host, port)};
  auto transport {make_shared<TBufferedTransport>(socket)};
  auto protocol {make_shared<TBinaryProtocol>(transport)};  //TODO: Allow for http[s]
  MapDClient client {MapDClient(protocol)};
  TSessionId session;
  
  //open the transport, which effectively makes the client active
  transport->open();
    
  //method to get session value from OmniSci
  client.connect(session, user_name, passwd, db_name);
  
  //TODO: this doesn't work, because R doesn't know how to translate MapDClient into an
  //R object. Also doesn't know how to deal with transport being a pointer to 
  //a thrift object
  // return List::create(_["transport"] = transport,
  //                     _["client"] = client,
  //                     _["session"] = session
  //                     );
  return Connection{transport, client, session};
  
}

// [[Rcpp::export]]
List proofofconcept() {
  
  string server_host{"randyzwitch-workstation"};
  unsigned int port{6274}; //don't need unsigned here, just indicates that port should be > 0
  string table_name{"mapd_states"};
  string db_name{"mapd"};
  string user_name{"mapd"};
  string passwd{"HyperInteractive"};
  
  // make_shared:
  // Allocates and constructs an object of type T passing args to its constructor,
  // and returns an object of type shared_ptr<T> that owns and stores a pointer to it (with a use count of 1)
  auto socket {make_shared<TSocket>(server_host, port)};
  auto transport {make_shared<TBufferedTransport>(socket)};
  auto protocol {make_shared<TBinaryProtocol>(transport)};
  auto client {MapDClient(protocol)};
  TSessionId session{};
  
  try {
    
    // -> both dereferences the pointer to get its data value and also lets you select a method from pointer value
    // alternative is (*transport).open();
    transport->open();  //transport is a pointer, so need to use -> instead of .
    client.connect(session, user_name, passwd, db_name);
    
    auto table_details = get_table_details(client, session, table_name);
    
    //debugging: This proves function call working, don't write to cout later
    std::cout << table_details << std::endl;
    
    //for values R can auto-convert, this is how you could get data from C++ to R
    //ideally, wouldn't be defining R translation functions inline like this
    //auto-generating the fields into R Lists would be cool
    //Need to understand how to register structs, enums and pointers in R
    //list below is incomplete
    return List::create(_["fragment_size"] = table_details.fragment_size,
                        _["page_size"] = table_details.page_size,
                        _["max_rows"] = table_details.max_rows,
                        _["view_sql"] = table_details.view_sql,
                        _["shard_count"] = table_details.shard_count,
                        _["key_metainfo"] = table_details.key_metainfo,
                        _["is_temporary"] = table_details.is_temporary
                        );
    
    client.disconnect(session);
    transport->close();
    
  // Seems like overkill once the functions actually written and tested  
  } catch (TMapDException& e) { //Catches MapDException first
    
    std::cerr << e.error_msg << std::endl;
    // return 1;
    
  } catch (TException& te) { //Then catches Thrift exception
    
    std::cerr << "Thrift error: " << te.what() << std::endl;
    // return 1;
    
  }
  
  return 0;
}