add_executable (base64enc src/base64enc.cpp src/base64_map.cpp)
add_executable (base64dec src/base64dec.cpp src/base64_map.cpp)
target_include_directories (base64enc PRIVATE include)
target_include_directories (base64dec PRIVATE include)
