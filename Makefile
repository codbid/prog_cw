.DEFAULT_GOAL = all
CC = gcc
CFLAGS = -Wall -Werror -Isrc/lib -MMD
TARGET = bin/palindrome
OBJDIR = obj
SRCDIR = src

SRC_PALINDROME_DIR = $(SRCDIR)/palindrome
SRC_LIB_DIR = $(SRCDIR)/lib
OBJ_PALINDROME_DIR = $(OBJDIR)/palindrome
OBJ_LIB_DIR = $(OBJDIR)/lib

SRC_PALINDROME = $(wildcard $(SRC_PALINDROME_DIR)/*.c)
OBJ_PALINDROME = $(patsubst $(SRC_PALINDROME_DIR)/%.c, $(OBJ_PALINDROME_DIR)/%.o, $(SRC_PALINDROME))
DEP_PALINDROME = $(OBJ_PALINDROME:.o=.d)

SRC_LIB = $(wildcard $(SRC_LIB_DIR)/*.c)
OBJ_LIB = $(patsubst $(SRC_LIB_DIR)/%.c, $(OBJ_LIB_DIR)/%.o, $(SRC_LIB))
DEP_LIB = $(OBJ_LIB:.o=.d)

PALINDROMEOBJS = $(OBJ_PALINDROME_DIR)/main.o
LIBOBJS = $(OBJ_LIB_DIR)/palindrome.o
LIBNAME = $(OBJ_LIB_DIR)/palindrome.a

.PHONY: all clean clean_all

all: $(TARGET)

$(TARGET): $(PALINDROMEOBJS) $(LIBNAME)
	$(CC) $^ -o $@

$(OBJ_PALINDROME_DIR)/%.o: $(SRC_PALINDROME_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_LIB_DIR)/%.o: $(SRC_LIB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBNAME): $(LIBOBJS)
	ar rcs $@ $^

-include $(DEP_PALINDROME)
-include $(DEP_LIB)

clean:
	$(RM) -r $(OBJ_PALINDROME_DIR)/* $(OBJ_LIB_DIR)/* $(LIBNAME)

clean_all:
	$(RM) -r $(OBJ_PALINDROME_DIR)/* $(OBJ_LIB_DIR)/* $(TARGET) $(LIBNAME)