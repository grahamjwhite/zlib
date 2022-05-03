
#include <Rcpp.h>
using namespace Rcpp;

#include <zlib.h>
#include <deque>

void checkInflateError(int err, z_streamp strm);

//' zlib version
//' 
// [[Rcpp::export]]
const char * version() {
  return zlib_version;
}

  
//' Compress a raw vector using zlib
//'
//' @param x a raw vector to be compressed
//' @param level the compression level as an integer from -1 to 9, where
//'1 means faster processing and less compression, 9 means the highest
//' compression but slowest processing. 0 perfoms no compression and -1
//' is the default which is a balance of speed and compression 
//' (currently equivalent to 6).
//' 
// [[Rcpp::export]]
Rcpp::RawVector compress(Rcpp::RawVector x, int level = -1) {
  
  unsigned char* xptr = (unsigned char*)&x[0];

  int err;
  uLong len = (uLong)x.size();
  uLong comprLen = compressBound(len);
  unsigned char* dest;
  dest = (Byte*)calloc((uInt)comprLen, 1);
  
  err = compress2(dest, &comprLen, xptr, len, level);
  
  if(err != Z_OK){
    Rcpp::stop(zError(err));
  }
  
  Rcpp::RawVector retVal(dest, dest + comprLen);
  
  free(dest);
  
  return retVal;
  
}

//' Decompress a compressed raw vector using zlib
//' 
//' @param x the compressed raw vector
//' @param wbits a parameter that controls the window size and type of header/trailer used.
//' Default is 15. See Details for more information. 
//' 
//' @section wbits parameter:
//' 
//' The windowBits parameter is the base two logarithm of the maximum window
//' size (the size of the history buffer).  It should be in the range 8..15 for
//' this version of the library. The default value is 15 if inflateInit is used
//' instead. windowBits must be greater than or equal to the windowBits value
//' provided to deflateInit2() while compressing, or it must be equal to 15 if
//' deflateInit2() was not used. If a compressed stream with a larger window
//' size is given as input, inflate() will return with the error code
//' Z_DATA_ERROR instead of trying to allocate a larger window.
//'    
//' windowBits can also be -8..-15 for raw inflate. In this case, -windowBits
//' determines the window size. inflate() will then process raw deflate data,
//' not looking for a zlib or gzip header, not generating a check value, and not
//' looking for any check values for comparison at the end of the stream. This
//' is for use with other formats that use the deflate compressed data format
//' such as zip.  Those formats provide their own check values. If a custom
//' format is developed using the raw deflate format for compressed data, it is
//' recommended that a check value such as an adler32 or a crc32 be applied to
//' the uncompressed data as is done in the zlib, gzip, and zip formats.  For
//' most applications, the zlib format should be used as is. Note that comments
//' above on the use in deflateInit2() applies to the magnitude of windowBits.
//'            
//' windowBits can also be greater than 15 for optional gzip decoding. Add
//' 32 to windowBits to enable zlib and gzip decoding with automatic header
//' detection, or add 16 to decode only the gzip format (the zlib format will
//' return a Z_DATA_ERROR).  If a gzip stream is being decoded, strm->adler is
//' a crc32 instead of an adler32.
//' 
//' @return a raw vector.
//'  
// [[Rcpp::export]]
Rcpp::RawVector decompress(Rcpp::RawVector x, int wbits = 15) {
  
  unsigned char* xptr = &x[0];
  uLong CHUNK = (uLong)x.size();
  std::deque<unsigned char> deq;
  int ret;
  unsigned have;
  z_stream strm;
  unsigned char out[CHUNK];
  
  /* allocate inflate state */
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  
  ret = inflateInit2(&strm, wbits);
  checkInflateError(ret, &strm);

  /* Read in the whole source vector */
    strm.avail_in = CHUNK;
    strm.next_in = xptr;
    
    /* run inflate() on input until output buffer not full */
    do {
      
      // use same size output buffer as the input vector, but doesn't have to be
      strm.avail_out = CHUNK;
      strm.next_out = out;
      
      ret = inflate(&strm, Z_NO_FLUSH);
      assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
    
      switch (ret) {
        case Z_NEED_DICT:
          ret = Z_DATA_ERROR;     /* and fall through */
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
          (void)inflateEnd(&strm);
          checkInflateError(ret, &strm);
      }
    
      have = CHUNK - strm.avail_out; /* number of bytes actually produced by inflate*/
      
      // write the output buffer to the back of the deque
      for(size_t i = 0; i < have; i++){
        deq.push_back(out[i]);
      }
    
    } while (strm.avail_out == 0); // loop while the output buffer is being filled
  
  /* clean up and return */
  (void)inflateEnd(&strm);
  return Rcpp::RawVector(deq.begin(), deq.end());
}


void checkInflateError(int err, z_streamp strm) {
  
  if(err != Z_OK){
    (void)inflateEnd(strm);
    Rcpp::stop(zError(err));
  }
  
}

