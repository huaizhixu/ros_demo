cmake_minimum_required(VERSION 3.0.2)
project(pinocchio_ros_example)

find_package(catkin REQUIRED COMPONENTS roscpp)

find_package(pinocchio REQUIRED)


catkin_package(
  # INCLUDE_DIRS include
  # LIBRARIES one_leg_description
  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
  # DEPENDS Eigen
)


add_executable(example src/example.cpp)
target_link_libraries(example ${catkin_LIBRARIES} pinocchio::pinocchio )

add_executable(hetor_pinocchio_test src/hetor_pinocchio_test.cpp)
target_link_libraries(hetor_pinocchio_test
${catkin_LIBRARIES}
${Eigen_LIBRARIES}
pinocchio::pinocchio)




install(TARGETS example
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

