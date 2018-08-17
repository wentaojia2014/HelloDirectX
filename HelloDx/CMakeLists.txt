get_filename_component(basename ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set (TAR ${basename})

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
add_executable(${TAR} ${SRC} ${CURRENT_HEADERS})
# target_link_libraries(${TAR} TaoMath)
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR})

install(TARGETS ${TAR} DESTINATION bin)
