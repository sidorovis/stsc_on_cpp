
find_package( Boost 1.41 ${SEARCH_PARAMETERS} COMPONENTS
	filesystem
	thread
	regex
	date_time
	system
	program_options
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
	shared_name_storage
)

add_source_list( ${module_name} common "common/*.cpp" )
add_source_list( ${module_name} common "common/*.h" )

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries ${module_name} system_utilities Boost )
