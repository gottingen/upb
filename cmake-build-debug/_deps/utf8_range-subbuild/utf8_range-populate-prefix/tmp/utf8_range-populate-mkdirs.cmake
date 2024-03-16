# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jeff/github/gottingen/upb/3rd/utf8_range"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-build"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/tmp"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/src/utf8_range-populate-stamp"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/src"
  "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/src/utf8_range-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/src/utf8_range-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jeff/github/gottingen/upb/cmake-build-debug/_deps/utf8_range-subbuild/utf8_range-populate-prefix/src/utf8_range-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
