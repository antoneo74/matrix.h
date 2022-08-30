.PHONY: all clean test s21_matrix.a check gcov_report
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PROFILE_FLAGS = -fprofile-arcs -ftest-coverage
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif
default: all

all: clean s21_matrix.a test gcov_report

test: s21_matrix.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) -o test unit_tests.c s21_matrix.a -lcheck -lgcov -coverage
	./test
else
	$(CC) $(CFLAGS) -o test unit_tests.c s21_matrix.a -lcheck -lsubunit -lrt -lpthread -lm -lgcov -coverage
	./test
endif

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib s21_matrix.a

s21_matrix.o:  s21_matrix.c s21_matrix.h
	$(CC) -c s21_matrix.c

clean:
	-rm -rf test s21_matrix *.out *.o *.a *.cfg fizz *.gc* *.info report unit_tests RESULT_VALGRIND.txt

rebuild: clean all

check:
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	rm CPPLINT.cfg

valgrind:
	valgrind --quiet --leak-check=full --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test

gcov_report:
ifeq ($(OS), Darwin)
	$(CC) --coverage $(PROFILE_FLAGS) unit_tests.c s21_matrix.c -o test -lcheck
else 
	$(CC) --coverage $(PROFILE_FLAGS) unit_tests.c s21_matrix.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	open ./report/index-sort-f.html
else
	xdg-open ./report/index-sort-f.html
endif
	rm -rf ./*.gcno ./*.gcda ./GcovReport.* 
