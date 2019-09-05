file (
    GLOB
    src
    sources/*.cpp
    )

add_library(menli
    SHARED
    ${src}
    )

target_include_directories(menli
    PUBLIC
    include
    )

target_link_libraries(menli
    PUBLIC
    numerical
    )

target_compile_features(menli
    PRIVATE
    cxx_variadic_templates
    )

install (TARGETS menli
    DESTINATION lib)

install (FILES ${headers}
    DESTINATION include/${CMAKE_PROJECT_NAME})

