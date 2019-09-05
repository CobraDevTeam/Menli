file (
    GLOB
    src
    sources/*.cpp
    )

add_library(numerical
    SHARED
    ${src}
    )

target_include_directories(numerical
    PUBLIC
    include
    )

target_compile_features(numerical
    PRIVATE
    cxx_variadic_templates
    )

install (TARGETS numerical
    DESTINATION lib)

install (FILES ${headers}
    DESTINATION include/${CMAKE_PROJECT_NAME})

