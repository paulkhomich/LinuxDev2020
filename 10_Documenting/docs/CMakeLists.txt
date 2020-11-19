find_package(Doxygen)
if (DOXYGEN_FOUND)
	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in)
	set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

	set(MAINPAGE_IN ${CMAKE_CURRENT_SOURCE_DIR}/guess.md.in)
	set(MAINPAGE_OUT ${CMAKE_CURRENT_BINARY_DIR}/guess.md)

	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	configure_file(${MAINPAGE_IN} ${MAINPAGE_OUT} @ONLY)
	message("Doxygen build started")

	add_custom_target( doc_doxygen ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM
	)
endif (DOXYGEN_FOUND)

find_program(HELP2MAN_FOUND help2man)
if (HELP2MAN_FOUND)
	add_custom_target( man_from_help ALL
		COMMAND help2man --no-info --output=guess.1 --name=${PROJECT_NAME} ./${PROJECT_NAME}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../
		COMMENT "Generating MAN page"
		VERBATIM
	)
endif(HELP2MAN_FOUND)
