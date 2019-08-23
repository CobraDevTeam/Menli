add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
    )

file (
    GLOB
    src
    sources/*.cpp
    )

file (
    GLOB
    headers
    include/*.hpp
    )

add_library(menli
    SHARED
    ${src}
    )

target_compile_features(menli
    PRIVATE
    cxx_variadic_templates
    )

install (TARGETS menli
    DESTINATION lib)

install (FILES ${headers}
    DESTINATION include/${CMAKE_PROJECT_NAME})

