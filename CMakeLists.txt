cmake_minimum_required(VERSION 3.12)
project(Hololang VERSION 1.6.2 LANGUAGES C CXX)

option(HOLOLANG_BUILD_TESTING "Build unit test executable" OFF)
set(HOLOLANG_CMD_NAME "hololang" CACHE STRING
	"Specifies the command-line Hololang executable filename")

set(HOLOLANG_HEADERS
	Hololang-cpp/src/Hololang/Dictionary.h
        Hololang-cpp/src/Hololang/List.h
	Hololang-cpp/src/Hololang/HololangErrors.h
	Hololang-cpp/src/Hololang/HololangInterpreter.h
	Hololang-cpp/src/Hololang/HololangIntrinsics.h
	Hololang-cpp/src/Hololang/HololangKeywords.h
	Hololang-cpp/src/Hololang/HololangLexer.h
	Hololang-cpp/src/Hololang/HololangParser.h
	Hololang-cpp/src/Hololang/HololangTAC.h
	Hololang-cpp/src/Hololang/HololangTypes.h
	Hololang-cpp/src/Hololang/QA.h
	Hololang-cpp/src/Hololang/RefCountedStorage.h
	Hololang-cpp/src/Hololang/SimpleString.h
	Hololang-cpp/src/Hololang/SimpleVector.h
	Hololang-cpp/src/Hololang/SplitJoin.h
	Hololang-cpp/src/Hololang/UnicodeUtil.h
	Hololang-cpp/src/Hololang/UnitTest.h
	
)

set(HOLOLANGCMD_HEADERS
	Hololang-cpp/src/DateTimeUtils.h
	Hololang-cpp/src/Key.h
	Hololang-cpp/src/OstreamSupport.h
	Hololang-cpp/src/ShellExec.h
	Hololang-cpp/src/ShellIntrinsics.h
	Hololang-cpp/src/editline/editline.h
	Hololang-cpp/src/editline/unix.h
	Hololang-cpp/src/whereami/whereami.h
)

add_library(Hololang-cpp
	Hololang-cpp/src/Hololang/Dictionary.cpp
	Hololang-cpp/src/Hololang/List.cpp
	Hololang-cpp/src/Hololang/HololangInterpreter.cpp
	Hololang-cpp/src/Hololang/HololangIntrinsics.cpp
	Hololang-cpp/src/Hololang/HololangKeywords.cpp
	Hololang-cpp/src/Hololang/HololangLexer.cpp
	Hololang-cpp/src/Hololang/HololangParser.cpp
	Hololang-cpp/src/Hololang/HololangTAC.cpp
	Hololang-cpp/src/Hololang/HololangTypes.cpp
	Hololang-cpp/src/Hololang/QA.cpp
	Hololang-cpp/src/Hololang/SimpleString.cpp
	Hololang-cpp/src/Hololang/SimpleVector.cpp
	Hololang-cpp/src/Hololang/SplitJoin.cpp
	Hololang-cpp/src/Hololang/UnicodeUtil.cpp
	Hololang-cpp/src/Hololang/UnitTest.cpp
	${HOLOLANG_HEADERS}
)

target_include_directories(Hololang-cpp PUBLIC Hololang-cpp/src/Hololang)

if(NOT WIN32)
	set(EDITLINE_SRC
		Hololang-cpp/src/editline/complete.c
		Hololang-cpp/src/editline/editline.c
		Hololang-cpp/src/editline/sysunix.c
	)
endif()

add_executable(Hololangcmd
	Hololang-cpp/src/main.cpp
	Hololang-cpp/src/DateTimeUtils.cpp
	Hololang-cpp/src/Key.cpp
	Hololang-cpp/src/OstreamSupport.cpp
	Hololang-cpp/src/ShellIntrinsics.cpp
	Hololang-cpp/src/ShellExec.cpp
	Hololang-cpp/src/whereami/whereami.c
	${EDITLINE_SRC}
	${HOLOLANGCMD_HEADERS}
)
target_include_directories(Hololangcmd PRIVATE Hololang-cpp/src/editline)
target_link_libraries(Hololangcmd PRIVATE Hololang-cpp)

set_target_properties(Hololang-cpp Hololangcmd PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON)
set_target_properties(Hololangcmd PROPERTIES OUTPUT_NAME ${HOLOLANG_CMD_NAME})

if(HOLOLANG_BUILD_TESTING)
	enable_testing()
	add_custom_target(TestSuite SOURCES TestSuite.txt)
	add_executable(tests-cpp Hololang-cpp/src/Hololang/UnitTest.cpp)
	target_compile_definitions(tests-cpp PRIVATE UNIT_TEST_MAIN)
	target_link_libraries(tests-cpp PRIVATE Hololang-cpp)
	add_test(NAME Hololang.cpp.UnitTests COMMAND tests-cpp)
	add_test(NAME Hololang.cpp.Integration COMMAND Hololangcmd --itest ${CMAKE_SOURCE_DIR}/TestSuite.txt)
	set_tests_properties(Hololang.cpp.UnitTests Hololang.cpp.Integration PROPERTIES FAIL_REGULAR_EXPRESSION "FAIL|Error")
endif()

install(TARGETS Hololang-cpp Hololangcmd)
