set(SOURCES point.h point.cpp)

add_library(math ${SOURCES})
target_include_directories(math INTERFACE ..)
