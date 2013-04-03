
find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	thread
	regex
	date_time
	system
	program_options
	serialization
)

find_package( system_utilities ${SEARCH_PARAMETERS} COMPONENTS
	logger
	ts_logger
	file_logger
	ts_queue
	queue_logger
	task_processor
	system_processor
	property_reader
	timer
	multikey_tree
	shared_name_storage
)

add_source_list( ${module_name} binary "binary/*.cpp" )
add_source_list( ${module_name} binary "binary/*.h" )
add_source_list( ${module_name} csv "csv/*.cpp" )
add_source_list( ${module_name} csv "csv/*.h" )

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries ${module_name} common system_utilities Boost )
