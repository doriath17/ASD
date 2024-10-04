cmake_minimum_required(VERSION 3.20)
project(RicorsioneToIterazione VERSION 1.0 LANGUAGES C CXX)

set(UTIL_DIR    ${CMAKE_SOURCE_DIR}/util)
add_library(util
    ${UTIL_DIR}/random.c
    ${UTIL_DIR}/array_util.c
    ${UTIL_DIR}/stackint.c
    ${UTIL_DIR}/stackptr.c
    ${UTIL_DIR}/timer.c 
    )
target_include_directories(util PUBLIC ${UTIL_DIR}/header)

set(SORTING_DIR ${CMAKE_SOURCE_DIR}/sorting)
add_library(sorting
    ${SORTING_DIR}/mergesort.c 
    ${SORTING_DIR}/heapsort.c 
)
target_include_directories(sorting PUBLIC ${SORTING_DIR}/header)
target_link_libraries(sorting PUBLIC util)

set(TREE_DIR ${CMAKE_SOURCE_DIR}/tree)
add_library(tree 
    ${TREE_DIR}/binary_tree.c 
    ${TREE_DIR}/bst.c 
    ${TREE_DIR}/bst_iter.c 

)
target_include_directories(tree PUBLIC ${TREE_DIR}/header)
target_link_libraries(tree PUBLIC util)

set(TESTING_DIR ${CMAKE_SOURCE_DIR}/testing)
add_library(testing 
    ${TESTING_DIR}/heapsort_test.c
    ${TESTING_DIR}/sorting_test.c 
    ${TESTING_DIR}/bst_test.c 
)
target_include_directories(testing PUBLIC ${TESTING_DIR}/header)
target_link_libraries(testing
    PUBLIC util
    PUBLIC sorting
    PUBLIC tree
)
target_link_libraries(testing PUBLIC sorting)

add_executable(${PROJECT_NAME} 
    main.c
)
target_link_libraries(${PROJECT_NAME} 
    PUBLIC util
    PUBLIC sorting 
    PUBLIC testing
    PUBLIC tree 
)