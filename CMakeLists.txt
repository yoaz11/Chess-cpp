cmake_minimum_required (VERSION 3.15)

project (Chess)

# New CMake versions map C++20 to /std:c++20 instead of c++latest, so <format>
# and other unstable ABI features aren't supported. Use C++23 for such versions
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else ()
    set(CMAKE_CXX_STANDARD 20)
endif ()

set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif ()

add_executable (Chess "../src/main.cpp" "../src/Chess.cpp"
        "../include/Board.h"
        "../include/Piece.h"
        "../include/Rook.h"
        include/Rook.h
        include/Board.h
        include/King.h
        src/Rook.cpp
        src/Board.cpp
        src/King.cpp
        include/Game.h
        src/Game.cpp
        include/Bishop.h
        src/Bishop.cpp
        include/Queen.h
        src/Queen.cpp
        include/Knight.h
        src/Knight.cpp
        include/Pawn.h
        src/Pawn.cpp
        include/PriorityQueue.h
        include/MoveSuggester.h
        src/MoveSuggester.cpp
        include/Move.h
        include/TopMoves.h
        src/TopMoves.cpp
        include/CustomExceptions.h
)


add_subdirectory (include)
add_subdirectory (src)



