#[[
This module downloads the CPM.cmake package manager script to a cached location, if it can't be found. Subsequent configuration runs will not require internet connection.

You can use the environment variable CPM_SOURCE_CACHE to control where the cache is set up; if not set, it will default to <top_level_source_dir>/Cache/.
]]

include_guard (GLOBAL)

if (COMMAND CPMAddPackage)
    return()
endif()

if (NOT DEFINED ENV{CPM_SOURCE_CACHE})
    if (CPM_Lemons_SOURCE)
        set (ENV{CPM_SOURCE_CACHE} "${CPM_Lemons_SOURCE}/Cache")
    else()
        set (ENV{CPM_SOURCE_CACHE} "${CMAKE_SOURCE_DIR}/Cache")
    endif()
endif()

set (LEMONS_CPM_PATH "$ENV{CPM_SOURCE_CACHE}/CPM.cmake" CACHE PATH "Path to the CPM.cmake script")
mark_as_advanced (FORCE LEMONS_CPM_PATH)

if (NOT EXISTS ${LEMONS_CPM_PATH})
    message (VERBOSE "Downloading CPM.cmake to ${LEMONS_CPM_PATH}")

    file (DOWNLOAD
      https://raw.githubusercontent.com/cpm-cmake/CPM.cmake/master/cmake/CPM.cmake
      ${LEMONS_CPM_PATH})
endif()

include (${LEMONS_CPM_PATH})
