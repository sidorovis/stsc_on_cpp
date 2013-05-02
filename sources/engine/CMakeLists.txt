
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

add_source_list( ${module_name} algorithms "algorithms/*.cpp" )
add_source_list( ${module_name} algorithms "algorithms/*.h" )

add_source_list( ${module_name} series_storage "series_storage/*.cpp" )
add_source_list( ${module_name} series_storage "series_storage/*.h" )

add_source_list( ${module_name} algorithms_storage "algorithms_storage/*.cpp" )
add_source_list( ${module_name} algorithms_storage "algorithms_storage/*.h" )

compile_project( ${module_name} "*.cpp" "*.h" STATIC libraries ${module_name} datafeed common system_utilities Boost )
