set(SOURCES k_means.h k_means.cpp)

add_library(k_means ${SOURCES})
target_include_directories(k_means INTERFACE ..)
