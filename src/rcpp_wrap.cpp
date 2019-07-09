#include "MapD.h"
#include <Rcpp.h>

namespace Rcpp {

    //TODO: define enums to return strings, remove static casts below?
    // template <> SEXP wrap(const TPartitionDetail& tpd);
    // template <> SEXP wrap(const TEncodingType& tet);
    // template <> SEXP wrap(const TDatumType& x){
    //   
    //   TDatumType y{x};
    //   
    //   switch(static_cast<int>(y))
    //   
    //   return List::create(_["TODO"] = 1);
    // 
    // };

    //structs
    template <> SEXP wrap(const TTypeInfo& x){

      return List::create(_["type"] = static_cast<int>(x.type),  //enum
                          _["encoding"] = static_cast<int>(x.encoding), //enum
                          _["nullable"] = x.nullable,
                          _["is_array"] = x.is_array,
                          _["precision"] = x.precision,
                          _["scale"] = x.scale,
                          _["comp_param"] = x.comp_param,
                          _["size"] = x.size
      );

    };

    template <> SEXP wrap(const TColumnType& x){

      return List::create(_["col_name"] = x.col_name,
                          _["col_type"] = x.col_type,
                          _["is_reserved_keyword"] = x.is_reserved_keyword,
                          _["src_name"] = x.src_name,
                          _["is_system"] = x.is_system,
                          _["is_physical"] = x.is_physical,
                          _["col_id"] = x.col_id
      );

    };

    template <> SEXP wrap(const TTableDetails& x){

      return List::create(_["fragment_size"] = x.fragment_size,
                          _["page_size"] = static_cast<int>(x.page_size),
                          _["max_rows"] = x.max_rows,
                          _["view_sql"] = x.view_sql,
                          _["shard_count"] = static_cast<int>(x.shard_count),
                          _["key_metainfo"] = x.key_metainfo,
                          _["is_temporary"] = x.is_temporary,
                          _["partition_detail"] = static_cast<int>(x.partition_detail), //enum
                          _["row_desc"] = x.row_desc
      );

    };

    template <> SEXP wrap(const TServerStatus& x){

      return List::create(_["read_only"] = x.read_only,
                          _["version"] = x.version,
                          _["rendering_enabled"] = x.rendering_enabled,
                          _["start_time"] = static_cast<Datetime>(x.start_time),
                          _["edition"] = x.edition,
                          _["host_name"] = x.host_name,
                          _["poly_rendering_enabled"] = x.poly_rendering_enabled,
                          _["role"] = static_cast<int>(x.role) //enum    
      );

    };
    
    template <> SEXP wrap(const TSessionInfo& x){
      
      return List::create(_["user"] = x.user,
                          _["database"] = x.database,
                          _["start_time"] = x.start_time
      );
      
    };
    
    template <> SEXP wrap(const TDBInfo& x){
      
      return List::create(_["db_name"] = x.db_name,
                          _["db_owner"] = x.db_owner);
      
    };

    template <> SEXP wrap(const TClusterHardwareInfo& x){
      
      return List::create(_["hardware_info"] = x.hardware_info);
      
    };
    
    template <> SEXP wrap(const THardwareInfo& x){
      
      return List::create(_["num_gpu_hw"] = x.num_gpu_hw,
                          _["num_cpu_hw"] = x.num_cpu_hw,
                          _["num_gpu_allocated"] = x.num_gpu_allocated,
                          _["start_gpu"] = x.start_gpu,
                          _["host_name"] = x.host_name,
                          _["gpu_info"] = x.gpu_info
                          );
      
    };
    
    template <> SEXP wrap(const TGpuSpecification& x){
      
      return List::create(_["num_sm"] = x.num_sm,
                          _["clock_frequency_kHz"] = x.clock_frequency_kHz,
                          _["memory"] = x.memory,
                          _["compute_capability_major"] = x.compute_capability_major,
                          _["compute_capability_minor"] = x.compute_capability_minor
                         );
      
    };
    
    template <> SEXP wrap(const TTableMeta& x){
      
      std::vector<int> dtypes;
      for(auto i: x.col_datum_types){
        dtypes.push_back(i);
      }
      
      return List::create(_["table_name"] = x.table_name,
                          _["num_cols"] = x.num_cols,
                          _["col_datum_types"] = dtypes, //enum
                          _["is_view"] = x.is_view,
                          _["is_replicated"] = x.is_replicated,
                          _["shard_count"] = x.shard_count,
                          _["max_rows"] = x.max_rows,
                          _["table_id"] = x.table_id,
                          _["max_table_id"] = x.max_table_id
                         );
    };
    
    template <> SEXP wrap(const TDatumVal& x){

      return List::create(_["int_val"] = x.int_val,
                          _["real_val"] = x.real_val,
                          _["str_val"] = x.str_val,
                          _["arr_val"] = x.arr_val
                          );
    };

    template <> SEXP wrap(const TDatum& x){

      return List::create(_["val"] = x.val,
                          _["is_null"] = x.is_null
                          );
      
    };
    
    template <> SEXP wrap(const TRow& x){
      
      return List::create(_["cols"] = x.cols);
      
    };
    
    template <> SEXP wrap(const TColumnData& x){

      return List::create(_["int_col"] = x.int_col,
                          _["real_col"] = x.real_col,
                          _["str_col"] = x.str_col,
                          _["arr_col"] = x.arr_col
                          );
      
    };
    
    template <> SEXP wrap(const TColumn& x){

      return List::create(_["data"] = x.data,
                          _["nulls"] = x.nulls);
      
    };
    
    template <> SEXP wrap(const TRowSet& x){
      
      return List::create(_["row_desc"] = x.row_desc,
                          _["rows"] = x.rows,
                          _["columns"] = x.columns,
                          _["is_columnar"] = x.is_columnar
                          );
      
    };
    
    template <> SEXP wrap(const TQueryResult& x){
      
      return List::create(_["row_set"] = x.row_set,
                          _["execution_time_ms"] = x.execution_time_ms,
                          _["total_time_ms"] = x.total_time_ms,
                          _["nonce"] = x.nonce
                          );
    };
    
} //end namespace
