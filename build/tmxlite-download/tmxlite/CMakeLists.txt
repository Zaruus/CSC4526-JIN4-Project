#
# For Tmxlite
#
# Contents inspired by https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project

project(tmxlite-download NONE)

include(ExternalProject)
ExternalProject_Add(tmxlite
  GIT_REPOSITORY    https://github.com/fallahn/tmxlite
  GIT_TAG           v1.2.1
  SOURCE_DIR        "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-src"
  BINARY_DIR        "C:/Users/pierr/source/repos/CSC4526-JIN4-Project/build/tmxlite-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
