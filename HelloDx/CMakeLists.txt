set (TAR HelloDx)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
aux_source_directory( . SRC)
aux_source_directory(Core SRC)
aux_source_directory(TaoMath SRC)
add_executable(${TAR} ${SRC} ${CURRENT_HEADERS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
set_target_properties(${TAR} PROPERTIES FOLDER ${TAR})
