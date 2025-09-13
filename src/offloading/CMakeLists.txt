build_lib(
  LIBNAME offloading
  SOURCE_FILES
    model/offloading-server.cc
    model/offloading-client.cc
    model/offloading-fifo.cc
  HEADER_FILES
    model/offloading-server.h
    model/offloading-client.h
    model/offloading-fifo.h
    model/offloading-decision.h
  LIBRARIES_TO_LINK
    ${libcore}
    ${libnetwork}
    ${libapplications}
)