// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// connect
List connect(std::string host, int port, std::string username, std::string password, std::string dbname);
RcppExport SEXP _ROmniSci_connect(SEXP hostSEXP, SEXP portSEXP, SEXP usernameSEXP, SEXP passwordSEXP, SEXP dbnameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::string >::type host(hostSEXP);
    Rcpp::traits::input_parameter< int >::type port(portSEXP);
    Rcpp::traits::input_parameter< std::string >::type username(usernameSEXP);
    Rcpp::traits::input_parameter< std::string >::type password(passwordSEXP);
    Rcpp::traits::input_parameter< std::string >::type dbname(dbnameSEXP);
    rcpp_result_gen = Rcpp::wrap(connect(host, port, username, password, dbname));
    return rcpp_result_gen;
END_RCPP
}
// disconnect
void disconnect(List conn);
RcppExport SEXP _ROmniSci_disconnect(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    disconnect(conn);
    return R_NilValue;
END_RCPP
}
// get_table_details
List get_table_details(List conn, std::string table_name);
RcppExport SEXP _ROmniSci_get_table_details(SEXP connSEXP, SEXP table_nameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    Rcpp::traits::input_parameter< std::string >::type table_name(table_nameSEXP);
    rcpp_result_gen = Rcpp::wrap(get_table_details(conn, table_name));
    return rcpp_result_gen;
END_RCPP
}
// get_server_status
List get_server_status(List conn);
RcppExport SEXP _ROmniSci_get_server_status(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_server_status(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_status
List get_status(List conn);
RcppExport SEXP _ROmniSci_get_status(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_status(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_version
CharacterVector get_version(List conn);
RcppExport SEXP _ROmniSci_get_version(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_version(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_tables
CharacterVector get_tables(List conn);
RcppExport SEXP _ROmniSci_get_tables(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_tables(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_users
CharacterVector get_users(List conn);
RcppExport SEXP _ROmniSci_get_users(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_users(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_physical_tables
CharacterVector get_physical_tables(List conn);
RcppExport SEXP _ROmniSci_get_physical_tables(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_physical_tables(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_views
CharacterVector get_views(List conn);
RcppExport SEXP _ROmniSci_get_views(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_views(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_session_info
List get_session_info(List conn);
RcppExport SEXP _ROmniSci_get_session_info(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_session_info(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_databases
List get_databases(List conn);
RcppExport SEXP _ROmniSci_get_databases(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_databases(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_hardware_info
List get_hardware_info(List conn);
RcppExport SEXP _ROmniSci_get_hardware_info(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_hardware_info(conn));
    return rcpp_result_gen;
END_RCPP
}
// get_tables_meta
List get_tables_meta(List conn);
RcppExport SEXP _ROmniSci_get_tables_meta(SEXP connSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    rcpp_result_gen = Rcpp::wrap(get_tables_meta(conn));
    return rcpp_result_gen;
END_RCPP
}
// switch_database
void switch_database(List conn, std::string dbname);
RcppExport SEXP _ROmniSci_switch_database(SEXP connSEXP, SEXP dbnameSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type conn(connSEXP);
    Rcpp::traits::input_parameter< std::string >::type dbname(dbnameSEXP);
    switch_database(conn, dbname);
    return R_NilValue;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ROmniSci_connect", (DL_FUNC) &_ROmniSci_connect, 5},
    {"_ROmniSci_disconnect", (DL_FUNC) &_ROmniSci_disconnect, 1},
    {"_ROmniSci_get_table_details", (DL_FUNC) &_ROmniSci_get_table_details, 2},
    {"_ROmniSci_get_server_status", (DL_FUNC) &_ROmniSci_get_server_status, 1},
    {"_ROmniSci_get_status", (DL_FUNC) &_ROmniSci_get_status, 1},
    {"_ROmniSci_get_version", (DL_FUNC) &_ROmniSci_get_version, 1},
    {"_ROmniSci_get_tables", (DL_FUNC) &_ROmniSci_get_tables, 1},
    {"_ROmniSci_get_users", (DL_FUNC) &_ROmniSci_get_users, 1},
    {"_ROmniSci_get_physical_tables", (DL_FUNC) &_ROmniSci_get_physical_tables, 1},
    {"_ROmniSci_get_views", (DL_FUNC) &_ROmniSci_get_views, 1},
    {"_ROmniSci_get_session_info", (DL_FUNC) &_ROmniSci_get_session_info, 1},
    {"_ROmniSci_get_databases", (DL_FUNC) &_ROmniSci_get_databases, 1},
    {"_ROmniSci_get_hardware_info", (DL_FUNC) &_ROmniSci_get_hardware_info, 1},
    {"_ROmniSci_get_tables_meta", (DL_FUNC) &_ROmniSci_get_tables_meta, 1},
    {"_ROmniSci_switch_database", (DL_FUNC) &_ROmniSci_switch_database, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_ROmniSci(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
