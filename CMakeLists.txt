cmake_minimum_required(VERSION 3.16)

project(miraya VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPANY "MirayaOSU")
set(IDENTIFIER "com.github.mirayaosu")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets WebSockets Network)
qt_standard_project_setup()

# ===========================Including Project Files===========================
set(FORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/forms")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(SOURCE_TWITCH_DIR "${CMAKE_SOURCE_DIR}/src/twitch")
set(SOURCE_GOSU_DIR "${CMAKE_SOURCE_DIR}/src/gosu")
set(SOURCE_OSUIRC_DIR "${CMAKE_SOURCE_DIR}/src/osuirc")
set(SOURCE_UTILS_DIR "${CMAKE_SOURCE_DIR}/src/utils")
set(SOURCE_SETUPWIZARD_DIR "${CMAKE_SOURCE_DIR}/src/setupwizard")
set(SOURCE_PREFERENCES_DIR "${CMAKE_SOURCE_DIR}/src/preferences")
set(SOURCE_SKINSURL_DIR "${CMAKE_SOURCE_DIR}/src/skinsurl")
set(SOURCE_COMMANDS_DIR "${CMAKE_SOURCE_DIR}/src/commands")
set(SOURCE_BACKUP_DIR "${CMAKE_SOURCE_DIR}/src/backup")

include_directories(${FORMS_DIR})
include_directories(${SOURCE_DIR})
include_directories(${SOURCE_TWITCH_DIR})
include_directories(${SOURCE_GOSU_DIR})
include_directories(${SOURCE_OSUIRC_DIR})
include_directories(${SOURCE_UTILS_DIR})
include_directories(${SOURCE_SETUPWIZARD_DIR})
include_directories(${SOURCE_PREFERENCES_DIR})
include_directories(${SOURCE_SKINSURL_DIR})
include_directories(${SOURCE_COMMANDS_DIR})
include_directories(${SOURCE_BACKUP_DIR})

file(GLOB_RECURSE SOURCES
	${FORMS_DIR}/*.cpp
	${SOURCE_TWITCH_DIR}/*.h
	${SOURCE_TWITCH_DIR}/*.cpp
	${SOURCE_GOSU_DIR}/*.h
	${SOURCE_GOSU_DIR}/*.cpp
	${SOURCE_OSUIRC_DIR}/*.h
	${SOURCE_OSUIRC_DIR}/*.cpp
	${SOURCE_UTILS_DIR}/*.h
	${SOURCE_UTILS_DIR}/*.cpp
	${SOURCE_SETUPWIZARD_DIR}/*.h
	${SOURCE_SETUPWIZARD_DIR}/*.cpp
	${SOURCE_PREFERENCES_DIR}/*.h
	${SOURCE_PREFERENCES_DIR}/*.cpp
	${SOURCE_SKINSURL_DIR}/*.h
	${SOURCE_SKINSURL_DIR}/*.cpp
	${SOURCE_COMMANDS_DIR}/*.h
	${SOURCE_COMMANDS_DIR}/*.cpp
	${SOURCE_BACKUP_DIR}/*.h
	${SOURCE_BACKUP_DIR}/*.cpp
	${SOURCE_DIR}/*.h
	${SOURCE_DIR}/*.cpp
	resources.qrc
)


# =========================== Executable ===========================
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})
set(CMAKE_AUTORCC ON)

# Add the executable
if (WIN32)
	add_executable(miraya WIN32 ${SOURCES})
	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		set_property(TARGET miraya PROPERTY WIN32_EXECUTABLE true)
	endif()
elseif(UNIX)
	add_executable(miraya ${SOURCES})
endif()



target_include_directories(miraya PRIVATE ${FORMS_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_TWITCH_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_GOSU_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_OSUIRC_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_UTILS_DIR})
target_include_directories(miraya PRIVATE ${SOURCE_SETUPWIZARD_DIR})

# =========================== linking libraries ===========================
target_link_libraries(miraya PRIVATE Qt6::Core)
target_link_libraries(miraya PRIVATE Qt6::Widgets)
target_link_libraries(miraya PRIVATE Qt6::WebSockets)
target_link_libraries(miraya PRIVATE Qt6::Network)
