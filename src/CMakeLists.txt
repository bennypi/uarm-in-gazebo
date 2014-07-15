cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(../include)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(UarmController SHARED UarmController.cc)
target_link_libraries(UarmController ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})


set (msgs
  ../msgs/uarm_new_joint_position_msgs.proto
)

set(msgs
  ../msgs/uarm_new_position_msgs.proto
  ../msgs/uarm_new_joint_position_msgs.proto
)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${msgs})
add_library(uarm_new_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(uarm_new_position_msgs ${PROTOBUF_LIBRARY})
add_library(uarm_new_joint_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(uarm_new_joint_position_msgs ${PROTOBUF_LIBRARY})
