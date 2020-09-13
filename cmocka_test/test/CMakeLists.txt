add_mocked_test(main SOURCES ${CMAKE_SOURCE_DIR}/src/main.c ${CMAKE_SOURCE_DIR}/src/sort.s MOCKS printf scanf fscanf fprintf main __isoc99_scanf)
