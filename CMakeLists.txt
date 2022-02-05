cmake_minimum_required (VERSION 3.21 FATAL_ERROR)

project (PsolaTest VERSION 0.0.1 LANGUAGES CXX)

include (AddLemons.cmake)

include (BVBrandFlags)
include (LemonsPluginModules)

juce_add_plugin (${PROJECT_NAME}
    ${BV_DEFAULT_BRAND_FLAGS}
    PRODUCT_NAME                  ${PROJECT_NAME}
    VERSION                       ${PROJECT_VERSION}
    NEEDS_MIDI_INPUT              TRUE
    NEEDS_MIDI_OUTPUT             FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS   FALSE
    IS_SYNTH                      FALSE
    IS_MIDI_EFFECT                FALSE
    MICROPHONE_PERMISSION_ENABLED TRUE
    MICROPHONE_PERMISSION_TEXT    "Imogen requires audio input to be able to produce its output. Please enable the microphone, or you won't hear any audio output."
    PLUGIN_NAME                   ${PROJECT_NAME}
    PLUGIN_CODE                   Psla
    FORMATS                       ${LEMONS_PLUGIN_FORMATS}
    DESCRIPTION                   "Real-time vocal harmonizer instrument"
    )

lemons_configure_juce_plugin (TARGET ${PROJECT_NAME} MICROPHONE)

target_sources (${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")

target_link_libraries (${PROJECT_NAME} PRIVATE lemons_psola LemonsPluginModules)
