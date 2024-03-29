################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 2.8.3)
project(dynamixel_workbench_operators)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_srvs
  std_msgs
  geometry_msgs
  sensor_msgs
  trajectory_msgs
  cmake_modules
  message_generation
  actionlib
  actionlib_msgs
)

# Resolve system dependency on yaml-cpp, which apparently does not
# provide a CMake find_package() module.
find_package(PkgConfig REQUIRED)
pkg_check_modules(YAML_CPP REQUIRED yaml-cpp)
find_path(YAML_CPP_INCLUDE_DIR
  NAMES yaml_cpp.h
  PATHS ${YAML_CPP_INCLUDE_DIRS}
)
find_library(YAML_CPP_LIBRARY
  NAMES YAML_CPP
  PATHS ${YAML_CPP_LIBRARY_DIRS}
)
link_directories(${YAML_CPP_LIBRARY_DIRS})

if(NOT ${YAML_CPP_VERSION} VERSION_LESS "0.5")
add_definitions(-DHAVE_NEW_YAMLCPP)
endif(NOT ${YAML_CPP_VERSION} VERSION_LESS "0.5")
################################################################################
#add service files
################################################################################

################################################################################
# Setup for python modules and scripts
################################################################################

################################################################################
# Declare ROS messages, services and actions
################################################################################
add_action_files(
   FILES
   joint_op.action
#   Action2.action
)

add_service_files(
  FILES
  pose_name.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
  actionlib_msgs
)
################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_srvs sensor_msgs trajectory_msgs geometry_msgs cmake_modules
)

################################################################################
# Build
################################################################################
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
)

add_executable(joint_action_client src/joint_action_client.cpp)
add_dependencies(joint_action_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(joint_action_client ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})


#add_executable(joint_operator src/joint_operator.cpp)
#add_dependencies(joint_operator ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(joint_operator ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})

add_executable(joint_operator_action src/joint_operator_action.cpp)
add_dependencies(joint_operator_action ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(joint_operator_action ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})

add_executable(service_caller src/service_caller.cpp)
add_dependencies(service_caller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service_caller ${catkin_LIBRARIES} )

add_executable(wheel_operator src/wheel_operator.cpp)
add_dependencies(wheel_operator ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(wheel_operator ${catkin_LIBRARIES})

add_executable(intro_publisher src/intro_publisher.cpp)
add_dependencies(intro_publisher ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(intro_publisher ${catkin_LIBRARIES})

#the below lines are commented because now using mqtt instead of file read write

#add_executable(trigger_catcher src/trigger_catcher.cpp)
#add_dependencies(trigger_catcher ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(trigger_catcher ${catkin_LIBRARIES})


#################################################################################
## Install
#################################################################################
#joint_operator
install(TARGETS 
 joint_action_client
 #joint_operator
 joint_operator_action
 wheel_operator 
 service_caller
 intro_publisher
 #trigger_catcher       commented because now using mqtt instead of file
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

install(DIRECTORY launch config
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
install(
   PROGRAMS
   scripts/trigger_catcher_mqtt.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
   )
################################################################################
# Test
################################################################################
