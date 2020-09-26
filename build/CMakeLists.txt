cmake_minimum_required(VERSION 3.10)

project(BasicEncryptorGUI)

add_executable(BasicEncryptorGUI
 source/BasicEncryptor.cpp
 source/BasicEncryptor.h
 source/RSA_Algorithm.cpp
 source/RSA_Algorithm.h
 source/BASICXOR_Algorithm.cpp
 source/BASICXOR_Algorithm.h
 source/wxAppLaunch.cpp
 source/wxAppLaunch.h
 source/wxMain.cpp
 source/wxMain.h
)

find_package(wxWidgets COMPONENTS net gl core base)
    if(wxWidgets_FOUND)
        include(${wxWidgets_USE_FILE})
        # and for each of your dependent executable/library targets:
        target_link_libraries(BasicEncryptorGUI ${wxWidgets_LIBRARIES})
    endif()