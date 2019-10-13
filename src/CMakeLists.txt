SET(SOURCE_LIST main.c eval.c builtin.c value_type.c read.c)

ADD_EXECUTABLE(src ${SOURCE_LIST})
TARGET_LINK_LIBRARIES(src lib)