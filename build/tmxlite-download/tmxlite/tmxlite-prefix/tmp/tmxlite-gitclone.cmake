
if(NOT "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitinfo.txt" IS_NEWER_THAN "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitclone-lastrun.txt")
  message(STATUS "Avoiding repeated git clone, stamp file is up to date: 'C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitclone-lastrun.txt'")
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  clone --no-checkout --config "advice.detachedHead=false" "https://github.com/fallahn/tmxlite" "tmxlite-src"
    WORKING_DIRECTORY "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build"
    RESULT_VARIABLE error_code
    )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once:
          ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/fallahn/tmxlite'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe"  checkout v1.2.1 --
  WORKING_DIRECTORY "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v1.2.1'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe"  submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src"
    RESULT_VARIABLE error_code
    )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy
    "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitinfo.txt"
    "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
  )
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-download/tmxlite/tmxlite-prefix/src/tmxlite-stamp/tmxlite-gitclone-lastrun.txt'")
endif()

