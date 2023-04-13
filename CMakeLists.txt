cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 11)

 project(sve-pattern-delay)

 add_subdirectory(dpf)

 dpf_add_plugin(sve-pattern-delay
   TARGETS clap lv2 vst2 vst3

   FILES_DSP
       source/sve-pattern-delay.cpp
       source/objects/delayLine.cpp
       source/patternGenerator.cpp
 )

 target_include_directories(sve-pattern-delay
   PUBLIC source)

 target_compile_options(sve-pattern-delay PUBLIC "-Wno-c++11-narrowing")

 add_compile_options(-fdiagnostics-color=always)
