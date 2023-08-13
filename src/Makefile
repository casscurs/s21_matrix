#Makefile by Casscurs

# Цвета для оформления вывода
COLOR_TITLE = \033[1;36m
COLOR_SUCCESS = \033[1;32m
COLOR_RESET = \033[0m

NAME = s21_matrix.a
SRC_FILES = $(wildcard *.c)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
DEP_FILES = $(patsubst %.c, %.d, $(SRC_FILES))

TESTS_DIR = tests/
TESTS_SRC = $(wildcard $(TESTS_DIR)*.c)
TESTS_OBJ = $(patsubst %.c,%.o,$(TESTS_SRC))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2 
AR = ar rcs
LIBS = -lcheck
COVERAGE = 

all : gcov_report

gcov_report: add_coverage test
	@echo "$(COLOR_TITLE)=== Running tests ===$(COLOR_RESET)"
	./test
	@echo "$(COLOR_TITLE)=====================$(COLOR_RESET)"
	mkdir -p report
	lcov -o report/test.info -c -d .
	genhtml -o report report/test.info
	@rm -rf *.gcda *.gcno tests/*.gcda tests/*.gcno

add_coverage:
	$(eval COVERAGE += --coverage)

test: $(NAME) $(TESTS_OBJ)
	$(CC) $(CFLAGS) $(COVERAGE) $(TESTS_OBJ) $(LIBS) $(NAME) -o $@

$(NAME) : $(OBJ_FILES)
	$(AR) $(NAME) $?
	@echo "$(COLOR_SUCCESS)=== Build complete ===$(COLOR_RESET)"

%.o : %.c
	$(CC) $(CFLAGS) $(COVERAGE) -c $< -o $@
	$(CC) $(CFLAGS) -MM -MF $(patsubst %.o, %.d, $@) $<

include $(wildcard $(D_FILES))

clean :
	@echo "$(COLOR_TITLE)=== Cleaning ===$(COLOR_RESET)"
	@rm -rf *.a *.o report *.gcda *.gcno $(DEP_FILES) test
	@rm -rf tests/*.d tests/*.o tests/*.gcda tests/*.gcno

cppcheck :
	@echo "$(COLOR_TITLE)=== Running cppcheck ===$(COLOR_RESET)"
	cppcheck --enable=all --suppress=missingIncludeSystem $(TESTS_DIR)

format :
	@echo "$(COLOR_TITLE)=== Formatting code ===$(COLOR_RESET)"
	clang-format -i -style=Google $(SRC_FILES) $(HEADER_FILES)
	clang-format -i -style=Google $(TESTS_SRC)


check-format :
	@echo "$(COLOR_TITLE)=== Checking code formatting ===$(COLOR_RESET)"
	clang-format -n -style=Google $(SRC_FILES) $(HEADER_FILES)

.PHONY : all clean cppcheck cpplint format check-format