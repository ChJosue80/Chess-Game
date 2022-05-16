
set(SOURCES bishop.cpp
            king.cpp
            rooke.cpp
            pawn.cpp
            knight.cpp
            pieces.cpp
            queen.cpp
            chessWindow.cpp)

add_library(pieces_lib ${SOURCES})

target_include_directories(pieces_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(pieces_lib
        PUBLIC
            Qt${QT_VERSION_MAJOR}::Widgets)