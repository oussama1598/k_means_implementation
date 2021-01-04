find_package(Threads REQUIRED)

set(SOURCES csv.hpp DataSet.h DataSet.cpp)

add_library(dataset ${SOURCES})
target_include_directories(dataset INTERFACE ..)
target_link_libraries(dataset PRIVATE Threads::Threads)
