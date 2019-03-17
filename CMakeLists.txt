cmake_minimum_required(VERSION 3.13)
project(DeepDarkFantasy)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)

include_directories(include)
include_directories(include/rapidjson)
include_directories(include/rapidjson/error)
include_directories(include/rapidjson/internal)
include_directories(include/rapidjson/msinttypes)

add_executable(DeepDarkFantasy
        include/rapidjson/error/en.h
        include/rapidjson/error/error.h
        include/rapidjson/internal/biginteger.h
        include/rapidjson/internal/diyfp.h
        include/rapidjson/internal/dtoa.h
        include/rapidjson/internal/ieee754.h
        include/rapidjson/internal/itoa.h
        include/rapidjson/internal/meta.h
        include/rapidjson/internal/pow10.h
        include/rapidjson/internal/regex.h
        include/rapidjson/internal/stack.h
        include/rapidjson/internal/strfunc.h
        include/rapidjson/internal/strtod.h
        include/rapidjson/internal/swap.h
        include/rapidjson/msinttypes/inttypes.h
        include/rapidjson/msinttypes/stdint.h
        include/rapidjson/allocators.h
        include/rapidjson/cursorstreamwrapper.h
        include/rapidjson/document.h
        include/rapidjson/encodedstream.h
        include/rapidjson/encodings.h
        include/rapidjson/filereadstream.h
        include/rapidjson/filewritestream.h
        include/rapidjson/fwd.h
        include/rapidjson/istreamwrapper.h
        include/rapidjson/memorybuffer.h
        include/rapidjson/memorystream.h
        include/rapidjson/ostreamwrapper.h
        include/rapidjson/pointer.h
        include/rapidjson/prettywriter.h
        include/rapidjson/rapidjson.h
        include/rapidjson/reader.h
        include/rapidjson/schema.h
        include/rapidjson/stream.h
        include/rapidjson/stringbuffer.h
        include/rapidjson/writer.h
        include/Item.cpp
        include/Action.cpp
        include/Creature.cpp
        include/functions.cpp
        include/cList.cpp
        include/combat.cpp
        include/room.cpp
        include/event.cpp
        include/statusEffect.cpp
        main.cpp)
