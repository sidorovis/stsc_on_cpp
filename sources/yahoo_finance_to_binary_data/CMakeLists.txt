
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
	system_processor
	property_reader
	timer
	shared_name_storage
)

compile_project( ${module_name} "*.cpp" "*.h" BINARY binaries ${module_name} common datafeed system_utilities Boost )
