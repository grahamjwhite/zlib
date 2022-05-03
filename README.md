
<!-- README.md is generated from README.Rmd. Please edit that file -->

# zlib

<!-- badges: start -->
<!-- badges: end -->

zlib provides access to the functions in the [zlib C
library](https://www.zlib.net/), using Rcpp.

## Example

This is a basic example which shows you how to solve a common problem:

``` r
library(zlib)

input_text <- "Some text to compress"

compressed_text <- zlib::compress(charToRaw(input_text))

decompressed_text <- rawToChar(zlib::decompress(compressed_text))

identical(input_text, decompressed_text)
#> [1] TRUE
```
