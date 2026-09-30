cmake_minimum_required(VERSION 3.14)
project(life C)
set(CMAKE_C_STANDARD 11)
enable_testing()

add_executable(test_life tests/test_life.c tests/mock_sim.c src/app.c)
target_include_directories(test_life PRIVATE src tests)
add_test(NAME life COMMAND test_life)

option(LIFE_BUILD_APP "Build graphical app" ON)
if(LIFE_BUILD_APP)
  find_package(SDL2 QUIET)
  if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found - downloading it with FetchContent")
    include(FetchContent)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_TEST OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                              GIT_TAG release-2.30.8 GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(SDL2)
    set(SDL_TARGET SDL2-static)
  elseif(TARGET SDL2::SDL2)
    set(SDL_TARGET SDL2::SDL2)
  else()
    set(SDL_TARGET ${SDL2_LIBRARIES})
  endif()
  add_executable(life src/start.c src/sim.c src/app.c)
  target_include_directories(life PRIVATE src ${SDL2_INCLUDE_DIRS})
  target_link_libraries(life PRIVATE ${SDL_TARGET})
endif()

find_program(CLANG_EXE clang)
if(CLANG_EXE)
  add_custom_target(ir
    COMMAND ${CLANG_EXE} -O2 -S -emit-llvm -I. app.c -o ../ir/app.ll
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src
    COMMENT "Generating ir/app.ll (-O2)")
endif()
