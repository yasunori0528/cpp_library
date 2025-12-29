cmake_minimum_required(VERSION 3.5.0)

project(primeqk VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    head.h

    time.h
    math.h
    miller_rabin.h
    pollard_rho.h
    trial_divition.h
    card.h
    hand.h
    max_prime.h
    min_prime.h
    search_composite.h

    #z_test.cpp
    #expanded_program/max_prime_expanded.cpp
    #expanded_program/max_prime_expanded_boost.cpp
    test/test_max_prime.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# マクロ定義
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<PLATFORM_ID:Windows>:__WINDOWS__>
    $<$<PLATFORM_ID:Linux>:__LINUX__>
)

# コンパイルオプション
target_compile_options(${PROJECT_NAME} PRIVATE 
    "-O3"
    "-mavx2" # for AVX2
    #"-march=skylake-avx512" # for AVX512
    "-mfma" # for FMA
    #"-no-fma"
)

# パス設定
set(GMP_DIR "D:/_others/prim/library/vcpkg/vcpkg/installed/x64-windows") # FIXME: 各自パス設定
set(BOOST_PATH "C:/Users/0108409038/Documents/Visual Studio 2022/boost_1_82_0") # FIXME: 各自パス設定
#set(MPI_DIR "")

# インクルード
target_include_directories(${PROJECT_NAME} PRIVATE
    "${GMP_DIR}/include"
    "${BOOST_PATH}"
    #"${MPI_DIR}/include"
)

# リンクディレクトリ
target_link_directories(${PROJECT_NAME} PRIVATE
    "${GMP_DIR}/lib"
)

# リンクライブラリ
target_link_libraries(${PROJECT_NAME} PRIVATE
    gmp
    gmpxx
    #$<$<PLATFORM_ID:Windows>:${MPI_DIR}/lib/release/impi.lib>
    #$<$<PLATFORM_ID:Linux>:${MPI_DIR}/lib/release/libmpi.a>
    #$<$<PLATFORM_ID:Linux>:${MPI_DIR}/lib/libmpicxx.a>
    #$<$<PLATFORM_ID:Linux>:"rt">
    #$<$<PLATFORM_ID:Linux>:"pthread">
)

# OpenMPの設定

find_package(OpenMP REQUIRED)

target_compile_options(${PROJECT_NAME} PRIVATE 
    "${OpenMP_CXX_FLAGS}"
    #"${OpenMP_CXX_FLAGS}-simd"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenMP::OpenMP_CXX
)
