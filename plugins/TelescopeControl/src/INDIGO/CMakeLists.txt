set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Threads REQUIRED)

SET(TelescopeControl_INDIGO_UIS
    TelescopeClientINDIGOWidget.ui
    INDIGOControlWidget.ui
    )

IF (${QT_VERSION_MAJOR} EQUAL "5")
     QT5_WRAP_UI(TelescopeControl_INDIGO_UIS_H ${TelescopeControl_INDIGO_UIS})
ELSE()
    QT_WRAP_UI(TelescopeControl_INDIGO_UIS_H ${TelescopeControl_INDIGO_UIS})
ENDIF()

add_library(TelescopeControl_INDIGO STATIC
    INDIGOConnection.hpp
    INDIGOConnection.cpp
    TelescopeClientINDIGO.hpp
    TelescopeClientINDIGO.cpp
    TelescopeClientINDIGOWidget.hpp
    TelescopeClientINDIGOWidget.cpp
    INDIGOControlWidget.hpp
    INDIGOControlWidget.cpp
    ${TelescopeControl_INDIGO_UIS_H}
    )

target_link_libraries(TelescopeControl_INDIGO
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    indiclient
    TelescopeControl_common
    ${CMAKE_THREAD_LIBS_INIT}
    )

target_include_directories(TelescopeControl_INDIGO INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

IF(ENABLE_TESTING)
    add_subdirectory(test)
ENDIF(ENABLE_TESTING)

SET_TARGET_PROPERTIES(TelescopeControl_INDIGO PROPERTIES FOLDER "plugins/TelescopeControl")
