cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(msgs)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/msgs)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(UarmController SHARED src/UarmController.cc)
target_link_libraries(UarmController new_joint_position_msgs new_position_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})
add_dependencies(UarmController new_joint_position_msgs new_position_msgs)

add_library(uarm_publisher src/uarm_publisher.cc)
target_link_libraries(uarm_publisher new_joint_position_msgs new_position_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES} )
add_dependencies(uarm_publisher new_joint_position_msgs new_position_msgs)

add_executable(uarm_pub src/uarm_pub.cc)
target_link_libraries(uarm_pub uarm_publisher)
add_dependencies(uarm_pub new_joint_position_msgs new_position_msgs)
