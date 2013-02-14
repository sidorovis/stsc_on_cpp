if (boost_process_ROOT)
	set(boost_process_ROOT ${boost_process_ROOT} )
elseif(NOT "$ENV{SYSTEM_UTILITIES_ROOT}" STREQUAL "")
	set(boost_process_ROOT $ENV{BOOST_PROCESS_ROOT} )
else()
	message(FATAL_ERROR "[ERROR]: No Boost.Process environment variable found")
endif()

find_path( boost_process_INCLUDE_DIR
			NAMES "boost/process.hpp"
			HINTS "${boost_process_ROOT}")

if( boost_process_FIND_REQUIRED AND (NOT boost_process_INCLUDE_DIR) )
		message(FATAL_ERROR " We can't find system_utilities ${component} component")
endif( boost_process_FIND_REQUIRED AND (NOT boost_process_INCLUDE_DIR) )

set(boost_process_INCLUDE_DIRS ${boost_process_INCLUDE_DIR})

if (NOT boost_process_FIND_QUIETLY)
	message(STATUS "boost_process_INCLUDE_DIRS = ${boost_process_INCLUDE_DIRS}")
endif()