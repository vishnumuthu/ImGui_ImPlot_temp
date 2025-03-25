cmake_minimum_required(VERSION 3.14)
project(ImGui_Temp)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

# GLAD
add_subdirectory(3rdparty/glad)

# NFD
add_subdirectory(3rdparty/nativefiledialog-extended)

# Fmt
find_package(fmt CONFIG REQUIRED)

# Spdlog
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
  common/App.h
  common/App.cpp
  common/Shader.h
  common/Native.h
  common/Native.cpp
  common/Image.h
  common/Fonts/Fonts.h
  common/Fonts/FontAwesome5.cpp
  common/Fonts/RobotoRegular.cpp
  common/Fonts/RobotoBold.cpp
  common/Fonts/RobotoItalic.cpp
  common/Fonts/RobotoMonoRegular.cpp
  common/Fonts/RobotoMonoBold.cpp
  common/Fonts/RobotoMonoItalic.cpp
  common/json.hpp
  common/stb_image.h
  common/stb_image_write.h
  common/ImGuiFileDialog.cpp
  common/ImGuiFileDialog.h
  common/ImGuiFileDialogConfig.h
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "common" "src")

target_include_directories(${PROJECT_NAME} PRIVATE "3rdparty")

target_link_libraries(${PROJECT_NAME} PRIVATE 
  ${OPENGL_LIBRARIES} 
  imgui::imgui
  implot::implot
  glfw 
  glad
  nfd
  fmt::fmt
  spdlog::spdlog
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)

