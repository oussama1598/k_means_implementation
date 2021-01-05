set(SOURCES k_means.h k_means.cpp ../math/point.h)

add_library(k_means ${SOURCES})
target_include_directories(k_means INTERFACE ..)
target_link_libraries(k_means PRIVATE math)
