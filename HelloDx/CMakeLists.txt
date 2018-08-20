get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TAR ${basename})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)

add_executable(${TAR} WIN32 ${SRC} ${CURRENT_HEADERS})
target_link_libraries(${TAR} TaoMath)
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR})
install(TARGETS ${TAR} DESTINATION bin)
