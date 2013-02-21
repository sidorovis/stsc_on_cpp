
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
)

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries ${module_name} common system_utilities Boost )
