
# ----------------------------------------------------------
# TEST
# ----------------------------------------------------------
enable_testing()

set(target "tests")

file(GLOB plugin_src
     ../src/*.h
     ../src/*.cpp
)

# These tests need their own main
file(GLOB test_src
    *.h
    *.cpp
)

juce_add_console_app(${target}
        VERSION "1.0.0"
        PRODUCT_NAME "SMOOTHIE"
        COMPANY_NAME ""
)

target_sources(${target}
   PRIVATE
        ${plugin_src}
        ${test_src}
)

add_test(NAME ${target} COMMAND "${target} -s")

target_include_directories(
    ${target}
    PUBLIC
    ../src
    ../tests
)

target_link_libraries(${target}
    PRIVATE
        Catch2::Catch2
        trompeloeil::trompeloeil
)

#add juce stuff
target_link_libraries(${target}
    PRIVATE
        # AudioPluginData           # If we'd created a binary data target, we'd link to it here
        juce::juce_audio_utils
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)