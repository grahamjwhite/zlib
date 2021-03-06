// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// version
const char * version();
RcppExport SEXP _zlib_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(version());
    return rcpp_result_gen;
END_RCPP
}
// compress
Rcpp::RawVector compress(Rcpp::RawVector x, int level);
RcppExport SEXP _zlib_compress(SEXP xSEXP, SEXP levelSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::RawVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type level(levelSEXP);
    rcpp_result_gen = Rcpp::wrap(compress(x, level));
    return rcpp_result_gen;
END_RCPP
}
// decompress
Rcpp::RawVector decompress(Rcpp::RawVector x, int wbits);
RcppExport SEXP _zlib_decompress(SEXP xSEXP, SEXP wbitsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::RawVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type wbits(wbitsSEXP);
    rcpp_result_gen = Rcpp::wrap(decompress(x, wbits));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_zlib_version", (DL_FUNC) &_zlib_version, 0},
    {"_zlib_compress", (DL_FUNC) &_zlib_compress, 2},
    {"_zlib_decompress", (DL_FUNC) &_zlib_decompress, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_zlib(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
