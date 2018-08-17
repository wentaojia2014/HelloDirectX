set (TAR TaoMath)
add_definitions(-DTAOMATHLIBRARY)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)
add_library(${TAR} SHARED ${SRC} ${CURRENT_HEADERS})
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR} LINKER_LANGUAGE CXX)

install(TARGETS ${TAR} DESTINATION lib)
install(FILES ${CURRENT_HEADERS} DESTINATION include/${TAR})