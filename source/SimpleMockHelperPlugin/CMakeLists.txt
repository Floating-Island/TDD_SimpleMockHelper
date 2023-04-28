# add subdirectories with CMakeLists
add_subdirectory(MockInterface)

# --- 'SimpleMockHelper' library ---

#create 'SimpleMockHelper' library
add_library(SimpleMockHelper STATIC)


set_target_properties(SimpleMockHelper PROPERTIES LINKER_LANGUAGE CXX)

# add public sources to 'SimpleMockHelper' library
target_sources(SimpleMockHelper
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/MockInterface/MockHelper/SimpleMockHelper.cpp
        ${CMAKE_CURRENT_LIST_DIR}/MockInterface/SimpleMockHelperInterface.cpp
    
    )

# set the public include directories to 'SimpleMockHelper' library
target_include_directories(SimpleMockHelper
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../ # this is to be able to use #include "SimpleMockHelperPlugin/..."
    )
# --------------------------