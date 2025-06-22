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

add_executable (Chess
        src/Piece.cpp
        include/Piece.h
        include/Board.h
        src/Board.cpp
        include/Rook.h
        src/Rook.cpp
        include/Bishop.h
        src/Bishop.cpp
        include/Knight.h
        src/Knight.cpp
        include/Queen.h
        src/Queen.cpp
        include/King.h
        src/King.cpp
        include/Pawn.h
        src/Pawn.cpp
        include/KingEnemies.h
        src/KingEnemies.cpp
        include/MyPriorityQueue.h
        include/Move.h
        src/MyPriorityQueue.cpp
        src/Move.cpp
        src/EvaluateAllMoves.cpp
        include/EvaluateAllMoves.h
        include/Exception.h
        include/Constants.h
        include/ThreadsPool.h
        include/ThreadSafePriorityQueue.h
)


add_subdirectory (include)
add_subdirectory (src)



