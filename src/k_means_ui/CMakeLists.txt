set(SOURCES main.cpp renderer.cpp renderer.h)

add_executable(k_means_ui ${SOURCES})
target_include_directories(k_means_ui INTERFACE ..)
target_link_libraries(k_means_ui PRIVATE k_means math CONAN_PKG::sdl2)
