#include "MapD.h"
#include <Rcpp.h>

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
                          _["col_type"] = tct.col_type,
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