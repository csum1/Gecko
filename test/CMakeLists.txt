list(APPEND CMAKE_MESSAGE_CONTEXT test)
set(testvar pinguin)
set(testvarc_ penguinscache CACHE INTERNAL "")
# FATAL_ERROR, SEND_ERROR, WARNING, AUTHOR_WARNING, DEPRECATION, NOTICE, STATUS, VERBOSE, DEBUG, TRACE
message(STATUS "test ${testvar} ${testvarc_}")
