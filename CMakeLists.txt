cmake_minimum_required(VERSION 3.6.3)
project(XAPI2)

# set compile parameter
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -fpermissive -rdynamic -std=c++11")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Wno-missing-field-initializers")
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
endif ()

# set output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# for vim plugin - YCM
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

# set use folder in vs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# thread
find_package(Threads)

# include and link directories
link_directories(
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

# add FIRST_API_CPP
file(GLOB_RECURSE FIRST_API_CPP_h ${CMAKE_CURRENT_LIST_DIR}/languages/CPP/FIRST_API_CPP/*.h)
file(GLOB_RECURSE FIRST_API_CPP_cpp ${CMAKE_CURRENT_LIST_DIR}/languages/CPP/FIRST_API_CPP/*.cpp)
list(FILTER FIRST_API_CPP_cpp EXCLUDE REGEX ".*dllmain.cpp")
if (WIN32)
    add_library(FIRST_API_CPP SHARED
            ${FIRST_API_h}
            ${FIRST_API_CPP_cpp}
            ${CMAKE_CURRENT_LIST_DIR}/include/FIRSTApi.h
            ${CMAKE_CURRENT_LIST_DIR}/include/CrossPlatform.h
            )
    set_target_properties(FIRST_API_CPP
            PROPERTIES
            FOLDER "languages/CPP"
            OUTPUT_NAME FIRST_API_CPP_$(PlatformTarget)
            )
else ()
    add_library(FIRST_API_CPP SHARED
            ${FIRST_API_CPP_cpp}
            )
endif ()
target_link_libraries(FIRST_API_CPP
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS}
        )
target_compile_definitions(FIRST_API_CPP
        PRIVATE BUILDING_DLL
        PUBLIC FIRST_API_CPP_h_EXPORTS)

# add XAPI_CPP
file(GLOB_RECURSE XAPI_CPP_h ${CMAKE_CURRENT_LIST_DIR}/languages/CPP/XAPI_CPP/*.h)
file(GLOB_RECURSE XAPI_CPP_cpp ${CMAKE_CURRENT_LIST_DIR}/languages/CPP/XAPI_CPP/*.cpp)
list(FILTER XAPI_CPP_cpp EXCLUDE REGEX ".*dllmain.cpp")
if (WIN32)
    add_library(XAPI_CPP SHARED
            ${XAPI_CPP_h}
            ${XAPI_CPP_cpp}
            ${CMAKE_CURRENT_LIST_DIR}/include/XApiC.h
            ${CMAKE_CURRENT_LIST_DIR}/include/XApiCpp.h
            ${CMAKE_CURRENT_LIST_DIR}/include/CrossPlatform.h
            )
    set_target_properties(XAPI_CPP
            PROPERTIES
            FOLDER "languages/CPP"
            OUTPUT_NAME XAPI_CPP_$(PlatformTarget)
            )
else ()
    add_library(XAPI_CPP SHARED
            ${XAPI_CPP_cpp}
            )
endif ()
target_link_libraries(XAPI_CPP
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS}
        )
target_compile_definitions(XAPI_CPP
        PRIVATE BUILDING_DLL
        PUBLIC XAPI_CPP_EXPORTS
        )

# get common files
set(common_h
        ${CMAKE_CURRENT_LIST_DIR}/include/toolkit.h
        ${CMAKE_CURRENT_LIST_DIR}/include/inirw.h
        ${CMAKE_CURRENT_LIST_DIR}/include/ChinaStock.h
        ${CMAKE_CURRENT_LIST_DIR}/include/IDGenerator.h
        ${CMAKE_CURRENT_LIST_DIR}/include/ApiProcess.h
        )
set(common_cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/toolkit.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/inirw.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/ChinaStock.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/IDGenerator.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/ApiProcess.cpp
        )
set(common_quote_h
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager.h
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager1.h
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager2.h
        ${CMAKE_CURRENT_LIST_DIR}/include/CSyntheticCalculate_DepthMarketDataNField.h
        )
set(common_quote_cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager1.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/CSubscribeManager2.cpp
        ${CMAKE_CURRENT_LIST_DIR}/include/CSyntheticCalculate_DepthMarketDataNField.cpp
        )
file(GLOB synthetic_h ${CMAKE_CURRENT_LIST_DIR}/include/synthetic/*.h)
file(GLOB synthetic_cpp ${CMAKE_CURRENT_LIST_DIR}/include/synthetic/*.cpp)

# functions
function(move_into_filter filter files)
    foreach (FILE ${files})
        # Get the directory of the source file
        get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

        # Remove common directory prefix to make the group
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")

        # Make sure we are using windows slashes
        string(REPLACE "/" "\\" GROUP "${GROUP}")

        source_group("${filter}" FILES "${FILE}")
    endforeach ()
endfunction(move_into_filter)

function(add_quote name folders)
    set(src_files "")
    set(h_files "")
    foreach (folder ${folders})
        file(GLOB tmp_h ${folder}/*.h)
        file(GLOB tmp_cpp ${folder}/*.cpp)
        list(APPEND h_files ${tmp_h})
        list(APPEND src_files ${tmp_cpp})
    endforeach (folder)

    list(FILTER src_files EXCLUDE REGEX ".*dllmain.cpp")

    if (WIN32)
        add_library(${name} SHARED
                ${h_files}
                ${src_files}
                ${common_h}
                ${common_cpp}
                ${common_quote_h}
                ${common_quote_cpp}
                ${synthetic_h}
                ${synthetic_cpp}
                )
        move_into_filter(common "${common_h}")
        move_into_filter(common "${common_cpp}")
        move_into_filter(common_quote "${common_quote_h}")
        move_into_filter(common_quote "${common_quote_cpp}")
        move_into_filter(synthetic "${synthetic_h}")
        move_into_filter(synthetic "${synthetic_cpp}")
    else ()
        add_library(${name} SHARED
                ${src_files}
                ${common_cpp}
                ${common_quote_cpp}
                ${synthetic_cpp}
                )
    endif ()

    target_include_directories(${name} PRIVATE
            ${folders}
            )
    target_compile_definitions(${name}
            PRIVATE USE_CMAKE BUILDING_DLL
            )
    if (WIN32)
        set_target_properties(${name}
                PROPERTIES
                FOLDER "apis"
                OUTPUT_NAME ${name}_$(PlatformTarget)
                )
    endif ()
endfunction(add_quote)

function(add_trade name folders)
    set(src_files "")
    set(h_files "")
    foreach (folder ${folders})
        file(GLOB tmp_h ${folder}/*.h)
        file(GLOB tmp_cpp ${folder}/*.cpp)
        list(APPEND h_files ${tmp_h})
        list(APPEND src_files ${tmp_cpp})
    endforeach (folder)

    list(FILTER src_files EXCLUDE REGEX ".*dllmain.cpp")

    if (WIN32)
        add_library(${name} SHARED
                ${h_files}
                ${src_files}
                ${common_h}
                ${common_cpp}
                ${synthetic_h}
                ${synthetic_cpp}
                )
        move_into_filter(common "${common_h}")
        move_into_filter(common "${common_cpp}")
        move_into_filter(synthetic "${synthetic_h}")
        move_into_filter(synthetic "${synthetic_cpp}")
    else ()
        add_library(${name} SHARED
                ${src_files}
                ${common_cpp}
                ${synthetic_cpp}
                )
    endif ()

    target_include_directories(${name} PRIVATE
            ${folders}
            )
    target_compile_definitions(${name}
            PRIVATE USE_CMAKE BUILDING_DLL
            )
    if (WIN32)
        set_target_properties(${name}
                PROPERTIES
                FOLDER "apis"
                OUTPUT_NAME ${name}_$(PlatformTarget)
                )
    endif ()
endfunction(add_trade)

function(add_apis name cpp_files h_files)
    list(FILTER cpp_files EXCLUDE REGEX ".*dllmain.cpp")

    if (WIN32)
        add_library(${name} SHARED
                ${h_files}
                ${cpp_files}
                ${common_h}
                ${common_cpp}
                ${common_quote_h}
                ${common_quote_cpp}
                ${synthetic_h}
                ${synthetic_cpp}
                )
        move_into_filter(common "${common_h}")
        move_into_filter(common "${common_cpp}")
        move_into_filter(common_quote "${common_quote_h}")
        move_into_filter(common_quote "${common_quote_cpp}")
        move_into_filter(synthetic "${synthetic_h}")
        move_into_filter(synthetic "${synthetic_cpp}")
    else ()
        add_library(${name} SHARED
                ${cpp_files}
                ${common_cpp}
                ${common_quote_cpp}
                ${synthetic_cpp}
                )
    endif ()

    target_compile_definitions(${name}
            PRIVATE USE_CMAKE BUILDING_DLL
            )
    if (WIN32)
        set_target_properties(${name}
                PROPERTIES
                FOLDER "apis"
                OUTPUT_NAME ${name}_$(PlatformTarget)
                )
    endif ()
endfunction(add_apis)

# add CTP Quote
set(folder "")
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP)
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP/Quote)
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP_Quote)
add_quote(CTP_Quote "${folder}")
if (WIN32)
    if (CMAKE_CL_64)
        ADD_CUSTOM_COMMAND(TARGET CTP_Quote
                PRE_LINK
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win64/thostmduserapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win64/thostmduserapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
                )
    else ()
        ADD_CUSTOM_COMMAND(TARGET CTP_Quote
                PRE_LINK
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win32/thostmduserapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win32/thostmduserapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
                )
    endif ()
else ()
    ADD_CUSTOM_COMMAND(TARGET CTP_Quote
            PRE_LINK
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/linux64/libthostmduserapi.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
            )
endif ()
target_link_libraries(CTP_Quote
        thostmduserapi
        )

# add CTP Trade
set(folder "")
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP)
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP/Trade)
list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/CTP_Trade)
add_trade(CTP_Trade "${folder}")
if (WIN32)
    if (CMAKE_CL_64)
        ADD_CUSTOM_COMMAND(TARGET CTP_Trade
                PRE_LINK
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win64/thosttraderapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win64/thosttraderapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
                )
    else ()
        ADD_CUSTOM_COMMAND(TARGET CTP_Trade
                PRE_LINK
                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win32/thosttraderapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/win32/thosttraderapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
                )
    endif ()
else ()
    ADD_CUSTOM_COMMAND(TARGET CTP_Trade
            PRE_LINK
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/CTP/linux64/libthosttraderapi.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
            )
endif ()
target_link_libraries(CTP_Trade
        thosttraderapi
        )

# add XTP Quote
#set(folder "")
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP)
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP/Quote)
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP_Quote)
#add_quote(XTP_Quote "${folder}")
#if (WIN32)
#    if (CMAKE_CL_64)
#        ADD_CUSTOM_COMMAND(TARGET XTP_Quote
#                PRE_LINK
#                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
#                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win64/xtpquoteapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
#                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win64/xtpquoteapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
#                )
#    else ()
#        ADD_CUSTOM_COMMAND(TARGET XTP_Quote
#                PRE_LINK
#                COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
#                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win32/xtpquoteapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
#                COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win32/xtpquoteapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
#                )
#    endif ()
#else ()
#    ADD_CUSTOM_COMMAND(TARGET XTP_Quote
#            PRE_LINK
#            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/linux64/libxtpquoteapi.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
#            )
#endif ()
#target_link_libraries(XTP_Quote
#        xtpquoteapi
#        )
#target_compile_definitions(XTP_Quote
#        PRIVATE USE_CMAKE BUILDING_DLL ISLIB
#        )

# add XTP Trade
#set(folder "")
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP)
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP/Trade)
#list(APPEND folder ${CMAKE_CURRENT_LIST_DIR}/apis/XTP_Trade)
#add_trade(XTP_Trade "${folder}")
#if (WIN32)
#	if (CMAKE_CL_64)
#		ADD_CUSTOM_COMMAND(TARGET XTP_Trade
#			PRE_LINK
#			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
#			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win64/xtptraderapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
#			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win64/xtptraderapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
#		)
#	else()
#		ADD_CUSTOM_COMMAND(TARGET XTP_Trade
#			PRE_LINK
#			COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
#			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win32/xtptraderapi.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)/
#			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/win32/xtptraderapi.lib ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$(Configuration)/
#		)
#	endif()
#else()
#	ADD_CUSTOM_COMMAND(TARGET XTP_Trade
#		PRE_LINK
#		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/include/XTP/linux64/libxtptraderapi.so ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
#	)
#endif()
#target_link_libraries(XTP_Trade
#	xtptraderapi
#)

# add cpp examples
add_executable(ExampleCTP ${CMAKE_CURRENT_LIST_DIR}/example/cpp/CTP/example_ctp.cpp)
target_link_libraries(ExampleCTP XAPI_CPP)
target_compile_definitions(ExampleCTP PRIVATE USE_CMAKE)
add_dependencies(ExampleCTP
        XAPI_CPP
        CTP_Quote
        CTP_Trade
        )

#add_executable(ExampleXTP ${CMAKE_CURRENT_LIST_DIR}/example/cpp/XTP/example_xtp.cpp)
#target_link_libraries(ExampleXTP XAPI_CPP)
#target_compile_definitions(ExampleXTP PRIVATE USE_CMAKE)
#add_dependencies(ExampleXTP
#	XAPI_CPP
#	XTP_Quote
#	XTP_Trade
#)

#set_target_properties(ExampleCTP ExampleXTP
#	PROPERTIES
#	FOLDER "example/CPP"
#)

set_target_properties(ExampleCTP
        PROPERTIES
        FOLDER "example/CPP")

# add first api examples
add_executable(ExampleFIRST ${CMAKE_CURRENT_LIST_DIR}/example/cpp/CTP/example_first.cpp)
target_link_libraries(ExampleFIRST FIRST_API_CPP)
target_compile_definitions(ExampleFIRST PRIVATE USE_CMAKE)
add_dependencies(ExampleFIRST
        FIRST_API_CPP
        CTP_Quote
        CTP_Trade)

set_target_properties(ExampleFIRST
        PROPERTIES
        FOLDER "example/CPP")