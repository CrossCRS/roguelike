cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(Roguelike)

find_package(SFML COMPONENTS system graphics window audio CONFIG REQUIRED)

set(sources
    "src/EntityManager.cpp"
    "src/ResourceManager.cpp"
    "src/Game.cpp"
    "src/main.cpp"
)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

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