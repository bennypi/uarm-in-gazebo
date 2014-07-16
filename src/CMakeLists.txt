cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(PROTOBUF_IMPORT_DIRS)
foreach(ITR ${GAZEBO_INCLUDE_DIRS})
  if(ITR MATCHES ".*gazebo-[0-9.]+$")
    set(PROTOBUF_IMPORT_DIRS "${ITR}/gazebo/msgs/proto")
  endif()
endforeach()

set (msgs
  ../msgs/new_joint_position.proto
)

set (msgs
  ../msgs/new_position.proto
  ../msgs/new_joint_position.proto
)

PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${msgs})

add_library(new_joint_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(new_joint_position_msgs ${PROTOBUF_LIBRARY})

add_library(new_position_msgs SHARED ${PROTO_SRCS})
target_link_libraries(new_position_msgs ${PROTOBUF_LIBRARY})

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(GAZEBO gazebo)
endif()
include_directories(../include)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../msgs)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

add_library(UarmController SHARED UarmController.cc)
target_link_libraries(UarmController new_joint_position_msgs new_position_msgs ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES} ${PROTOBUF_LIBRARIES})
add_dependencies(UarmController new_joint_position_msgs new_position_msgs)