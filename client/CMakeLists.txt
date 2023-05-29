cmake_minimum_required(VERSION 3.0.2)
 
project(client)
 
find_package(catkin REQUIRED COMPONENTS
  roscpp
)
 
## System dependencies are found with CMake's conventions
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
 
set(proto_dir ${PROJECT_SOURCE_DIR}/proto)
file(GLOB proto_files "${proto_dir}/*.proto")
 
# Set up destination directories
catkin_destinations()
set(proto_gen_dir ${CATKIN_DEVEL_PREFIX}/${CATKIN_GLOBAL_INCLUDE_DESTINATION}/proto)
set(proto_gen_cpp_dir ${proto_gen_dir})
file(MAKE_DIRECTORY ${proto_gen_dir})
file(MAKE_DIRECTORY ${proto_gen_cpp_dir})
set(protogen_include_dirs ${proto_gen_cpp_dir}/../ ${proto_gen_python_dir})
 
# Create lists of files to be generated
set(proto_gen_cpp_files "")
foreach(proto_file ${proto_files})  
  get_filename_component(proto_name ${proto_file} NAME_WE)
  list(APPEND proto_gen_cpp_files 
       ${proto_gen_cpp_dir}/${proto_name}.pb.h 
       ${proto_gen_cpp_dir}/${proto_name}.pb.cc
  )
endforeach(proto_file ${proto_files}) 
 
# Run protoc and generate language-specific headers.
add_custom_command(
  OUTPUT ${proto_gen_cpp_files}
  COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} --proto_path=${proto_dir} --cpp_out=${proto_gen_cpp_dir} ${proto_files}
  DEPENDS ${PROTOBUF_PROTOC_EXECUTABLE} ${proto_files}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
 
set_source_files_properties(${proto_gen_cpp_files} PROPERTIES GENERATED TRUE)
 
add_custom_target(${PROJECT_NAME}_generate_headers
  DEPENDS ${proto_gen_cpp_files} 
) 
 
# Create proto library for lining.
include_directories(${PROTOBUF_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR}/../../)
add_library(${PROJECT_NAME}_proto ${proto_gen_cpp_files})
target_link_libraries(${PROJECT_NAME}_proto ${PROTOBUF_LIBRARY})
add_dependencies(${PROJECT_NAME}_proto ${PROJECT_NAME}_generate_headers)
 
catkin_package(
  INCLUDE_DIRS ${protogen_include_dirs}
  LIBRARIES ${PROJECT_NAME}_proto
)
 
install(TARGETS ${PROJECT_NAME}_proto
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
 
install(DIRECTORY ${proto_gen_cpp_dir}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
 
catkin_package(
  INCLUDE_DIRS include 
)
 
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIR}
  ${CATKIN_DEVEL_PREFIX}
  include
)
 
add_library(${PROJECT_NAME}
  include/${PROJECT_NAME}/client.cc
)
 
add_executable(client_node src/client_node.cc include/${PROJECT_NAME}/client.cc)
 
target_link_libraries(${PROJECT_NAME}_node 
  ${catkin_LIBRARIES}
  ${PROTOBUF_LIBRARIES}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)



# add_executable(yuquan_listener src/yuquan_listener.cpp)
# target_link_libraries(yuquan_listener ${catkin_LIBRARIES}    
# ${PROTOBUF_LIBRARIES}
# ${Boost_FILESYSTEM_LIBRARY}
# ${Boost_SYSTEM_LIBRARY})
# add_executable(yuquan_talker src/yuquan_talker.cpp)
# target_link_libraries(yuquan_talker ${catkin_LIBRARIES}    
# ${PROTOBUF_LIBRARIES}
# ${Boost_FILESYSTEM_LIBRARY}
# ${Boost_SYSTEM_LIBRARY})

