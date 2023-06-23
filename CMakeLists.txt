cmake_minimum_required(VERSION 3.16)

project(miraya VERSION 1.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPANY "MirayaProject")
set(IDENTIFIER "com.github.MirayaProject")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets WebSockets Network)
qt_standard_project_setup()

# ===========================Including Project Files===========================
set(FORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/forms")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(SOURCE_STREAMING_SERVICES_DIR "${CMAKE_SOURCE_DIR}/src/services/streaming")
set(SOURCE_TWITCH_DIR "${CMAKE_SOURCE_DIR}/src/services/streaming/twitch")
set(SOURCE_OSU_DIR "${CMAKE_SOURCE_DIR}/src/osu")
set(SOURCE_UTILS_DIR "${CMAKE_SOURCE_DIR}/src/utils")
set(SOURCE_SETUPWIZARD_DIR "${CMAKE_SOURCE_DIR}/src/setupwizard")
set(SOURCE_PREFERENCES_DIR "${CMAKE_SOURCE_DIR}/src/preferences")
set(SOURCE_SKINSURL_DIR "${CMAKE_SOURCE_DIR}/src/skinsurl")
set(SOURCE_COMMANDS_DIR "${CMAKE_SOURCE_DIR}/src/commands")
set(SOURCE_BACKUP_DIR "${CMAKE_SOURCE_DIR}/src/backup")
set(SOURCE_UPDATER_DIR "${CMAKE_SOURCE_DIR}/src/updater")
set(SOURCE_THEME_DIR "${CMAKE_SOURCE_DIR}/src/theme")
set(SOURCE_ABOUT_DIR "${CMAKE_SOURCE_DIR}/src/about")


include_directories(
	${FORMS_DIR}
	${SOURCE_DIR}
	${SOURCE_STREAMING_SERVICES_DIR}
	${SOURCE_TWITCH_DIR}
	${SOURCE_OSU_DIR}
	${SOURCE_UTILS_DIR}
	${SOURCE_SETUPWIZARD_DIR}
	${SOURCE_PREFERENCES_DIR}
	${SOURCE_SKINSURL_DIR}
	${SOURCE_COMMANDS_DIR}
	${SOURCE_BACKUP_DIR}
	${SOURCE_UPDATER_DIR}
	${SOURCE_THEME_DIR}
	${SOURCE_ABOUT_DIR}
)

file(GLOB_RECURSE SOURCES
	${FORMS_DIR}/*.cpp
	${SOURCE_STREAMING_SERVICES_DIR}/*.h
	${SOURCE_STREAMING_SERVICES_DIR}/*.cpp
	${SOURCE_TWITCH_DIR}/*.h
	${SOURCE_TWITCH_DIR}/*.cpp
	${SOURCE_OSU_DIR}/*.h
	${SOURCE_OSU_DIR}/*.cpp
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
	${SOURCE_UPDATER_DIR}/*.h
	${SOURCE_UPDATER_DIR}/*.cpp
	${SOURCE_THEME_DIR}/*.h
	${SOURCE_THEME_DIR}/*.cpp
	${SOURCE_ABOUT_DIR}/*.h
	${SOURCE_ABOUT_DIR}/*.cpp
	${SOURCE_DIR}/*.h
	${SOURCE_DIR}/*.cpp
	resources.qrc
)


# =========================== Executable ===========================
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})
set(CMAKE_AUTORCC ON)

# Add the executable
if (WIN32)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/icon.o
		COMMAND windres icon.rc -o ${CMAKE_CURRENT_BINARY_DIR}/icon.o
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS icon.rc
	)
	add_custom_target(icon ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/icon.o)

	add_executable(miraya WIN32 ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/icon.o)
	if (CMAKE_BUILD_TYPE STREQUAL "Release")
		set_property(TARGET miraya PROPERTY WIN32_EXECUTABLE true)
	endif()
elseif(UNIX)
	add_executable(miraya ${SOURCES})
endif()



target_include_directories(miraya PRIVATE
	${FORMS_DIR}
	${SOURCE_DIR}
	${SOURCE_TWITCH_DIR}
	${SOURCE_OSU_DIR}
	${SOURCE_UTILS_DIR}
	${SOURCE_SETUPWIZARD_DIR}
)
# =========================== linking libraries ===========================
target_link_libraries(miraya PRIVATE Qt6::Core Qt6::Widgets Qt6::WebSockets Qt6::Network)
