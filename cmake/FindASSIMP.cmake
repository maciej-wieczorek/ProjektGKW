set( _assimp_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/include"
"C:/Program Files (x86)/assimp/include" )
set( _assimp_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib"
"C:/Program Files (x86)/glfw/lib-msvc110" )

# Check environment for root search directory
set( _assimp_ENV_ROOT $ENV{ASSIMP_ROOT} )
if( NOT ASSIMP_ROOT AND _assimp_ENV_ROOT )
	set(ASSIMP_ROOT ${_assimp_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( ASSIMP_ROOT )
	list( INSERT _assimp_HEADER_SEARCH_DIRS 0 "${ASSIMP_ROOT}/include" )
	list( INSERT _assimp_LIB_SEARCH_DIRS 0 "${ASSIMP_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(ASSIMP_INCLUDE_DIR "assimp/"
PATHS ${_assimp_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(ASSIMP_LIBRARY NAMES assimp
PATHS ${_assimp_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ASSIMP DEFAULT_MSG
ASSIMP_LIBRARY ASSIMP_INCLUDE_DIR)
