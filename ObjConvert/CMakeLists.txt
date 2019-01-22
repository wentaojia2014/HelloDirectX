get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TAR ${basename})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)

add_executable(${TAR} ${SRC} ${CURRENT_HEADERS})
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR})
set_target_properties(${TAR} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/run)
install(TARGETS ${TAR} DESTINATION bin)
