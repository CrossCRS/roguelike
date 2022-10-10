cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

project(Roguelike)

find_package(SFML COMPONENTS system graphics window audio CONFIG REQUIRED)

set(sources
    "src/Game.cpp"
	"src/main.cpp"
)

add_executable(${PROJECT_NAME} ${sources})

file(COPY data DESTINATION .)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY data/ DESTINATION bin)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system
    sfml-graphics
    sfml-window
    sfml-audio
)
