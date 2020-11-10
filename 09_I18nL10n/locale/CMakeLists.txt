add_custom_target(tr ALL
	DEPENDS ${CMAKE_SOURCE_DIR}/main.c	
)
add_custom_command(TARGET tr
	COMMAND xgettext -k___ -c ${CMAKE_SOURCE_DIR}/main.c -o messages.new.pot
	COMMAND cp ${CMAKE_SOURCE_DIR}/locale/guess.pot messages.pot
	COMMAND msgmerge -U messages.pot messages.new.pot

	COMMAND [ -f "ru.po" ] && msgmerge -U ru.po messages.pot || msginit -i messages.pot -o ru.po -l ru
)

add_custom_target(mo ALL
	DEPENDS tr
	DEPENDS ru.po
)
add_custom_command(TARGET mo
	COMMAND mkdir -p ${CMAKE_BINARY_DIR}/ru/LC_MESSAGES
	COMMAND msgfmt ru.po -o ${CMAKE_BINARY_DIR}/ru/LC_MESSAGES/guess.mo
)

set(GENERATES "${CMAKE_BINARY_DIR}/locale/messages.new.pot" "${CMAKE_BINARY_DIR}/locale/messages.pot" "${CMAKE_BINARY_DIR}/locale/messages.pot~" "${CMAKE_BINARY_DIR}/ru")
set_directory_properties( PROPERTIES
	ADDITIONAL_CLEAN_FILES "${GENERATES}" 
)
