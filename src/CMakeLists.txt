set(SOURCE_FILES CommandLineParser.cpp CommandLineParser.h config.h CopyFileRecursive.cpp RecursiveCopier.cpp RecursiveCopier.h)

find_package(Boost COMPONENTS program_options filesystem system REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(CopyRecursive ${SOURCE_FILES})
target_link_libraries( CopyRecursive ${Boost_LIBRARIES} )


install(TARGETS CopyRecursive DESTINATION bin)
