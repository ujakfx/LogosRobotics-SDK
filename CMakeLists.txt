cmake_minimum_required(VERSION 3.20)

project(LogosRoboticsSDK
    VERSION 0.0.1
    DESCRIPTION "Educational Open-Source Robotics Motion Control SDK"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------------------------------
# SDK Library
# -------------------------------------------------------

add_library(LogosRoboticsSDK

    # Kinematics
    src/kinematics/CoreXYKinematics.cpp

    # Motion
    src/motion/MotionEngine.cpp
    
    src/motion/HomingController.cpp

    # Planner
    src/planner/LinearMotionPlanner.cpp

    # HAL
    src/hal/DesktopMockHal.cpp
)

target_include_directories(LogosRoboticsSDK PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

# -------------------------------------------------------
# Tests
# -------------------------------------------------------

add_executable(CoreXYKinematics_Test
    tests/CoreXYKinematics_Test.cpp
)

target_link_libraries(CoreXYKinematics_Test
    LogosRoboticsSDK
)

add_executable(MotionEngine_Test
    tests/MotionEngine_Test.cpp
)

target_link_libraries(MotionEngine_Test
    LogosRoboticsSDK
)