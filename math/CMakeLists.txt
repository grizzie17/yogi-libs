set( BINARY Yogi_math_lib)


set( SOURCES
        trigonometry/conversions.cpp
        )


add_library(${BINARY} STATIC ${SOURCES})

include_directories(linear_algebra)
include_directories(trigonometry)

# add_executable(${BINARY}_run ${SOURCES})

add_subdirectory(test)
