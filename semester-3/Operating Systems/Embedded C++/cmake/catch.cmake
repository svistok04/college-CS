macro(fetch_catch _test_dir)
    set(CATCH_HEADER "${_test_dir}/catch.hpp")

    if (NOT EXISTS ${CATCH_HEADER})
        set(CATCH_URL "https://raw.githubusercontent.com/catchorg/Catch2/de6fe184a9ac1a06895cdd1c9b437f0a0bdf14ad/single_include/catch2/catch.hpp")
        file(DOWNLOAD ${CATCH_URL} ${CATCH_HEADER} SHOW_PROGRESS)
        unset(CATCH_URL)
    endif ()

    include_directories("${_test_dir}")
endmacro()