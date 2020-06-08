
if(NOT STANDARD_PROJECT_SETTINGS_DONE)
    set(STANDARD_PROJECT_SETTINGS_DONE TRUE)

    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(isMultiConfig)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile" CACHE STRING "" FORCE)
    else()
        if(NOT CMAKE_BUILD_TYPE)
            message("Defaulting to Release build.")
            set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
        endif()
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose build type")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;Profile")
    endif()
endif()