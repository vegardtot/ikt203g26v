# CMakeList.txt : CMake project for Submission-01, include source and define
# project specific logic here.
#

#add_library(stb_json INTERFACE)

#target_compile_definitions(stb_json INTERFACE STB_JSON_IMPLEMENTATION)
#target_compile_features(stb_json INTERFACE c_std_99)


# Add source to this project's executable.
add_executable (Submission-05 "main.cpp")
target_link_libraries(Submission-05 PRIVATE LibExample)

if (CMAKE_VERSION VERSION_GREATER 3.20)
  set_property(TARGET Submission-05 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
