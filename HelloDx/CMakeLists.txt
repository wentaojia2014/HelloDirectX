get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TAR ${basename})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)

include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib/x64)

add_executable(${TAR} WIN32 ${SRC} ${CURRENT_HEADERS})
target_link_libraries(${TAR} TaoMath)
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR})
install(TARGETS ${TAR} DESTINATION bin)

configure_file(vertex.shader ${CMAKE_BINARY_DIR}/${TAR}/vertex.shader)
configure_file(pixel.shader ${CMAKE_BINARY_DIR}/${TAR}/pixel.shader)
configure_file(seafloor.dds ${CMAKE_BINARY_DIR}/${TAR}/seafloor.dds)
