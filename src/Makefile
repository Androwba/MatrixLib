CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
GCOV_FLAGS= -fprofile-arcs -ftest-coverage
FIND&CHECK=$(wildcard *.cc *.h)

OS=$(shell uname)

ifeq ($(OS), Linux)
	OPEN = xdg-open
	LIBS= -lgtest -lpthread -pthread -lrt -lm -lsubunit
	LEAKS= valgrind --undef-value-errors=yes --track-origins=yes --leak-check=full -s ./matrix_test
else
	OPEN = open
	LIBS= -lgtest -pthread
	LEAKS= leaks -atExit -- ./matrix_test
endif

all: clean gcov_report

s21_matrix_oop.a: s21_matrix_oop.o 
	@ar crs $@ $^

s21_matrix_oop.o: s21_matrix_oop.cc
	@g++ -o s21_matrix_oop.o $^ -c

test:
	@$(CC) $(CFLAGS) s21_matrix_oop.cc s21_test.cc $(LIBS) -o matrix_test -lgtest -lgtest_main
	@./matrix_test

gcov_report: clean
	$(CC) $(GCOV_FLAGS) s21_matrix_oop.cc s21_test.cc $(LIBS) -o matrix_test
	-./matrix_test
	gcov matrix_test_gcov
	lcov -t "matrix_test" -o matrix_oop.info -c -d . --no-external
	lcov -r matrix_oop.info "*test*" -o matrix_oop.info
	genhtml -o report matrix_oop.info
	$(OPEN) ./report/index.html

google:
ifeq ("","$(wildcard ./.clang-format)")
	@cp -f ../materials/linters/.clang-format .
endif
	clang-format -i $(FIND&CHECK) 
	@rm .clang-format

style:
	@echo "\033[96m◄----------------------- Style Test -----------------------►\033[0m"
ifeq ("","$(wildcard ./.clang-format)")
	@cp -f ../materials/linters/.clang-format .
endif
	@clang-format -n $(FIND&CHECK) 
	@echo "\033[92mTest Done\033[0m"
	@rm .clang-format

cppcheck:
	@echo "\033[92m◄----------------------- CPP ------------------------------►\033[0m"
	@cppcheck --language=c++ *.cc *.h

leaks: test
	@echo "\033[92m◄----------------------- Leaks ----------------------------►\033[0m"
	$(LEAKS)

check: style cppcheck leaks

clean:
	@rm -rf *.o *.so *.a *.gc* *.info report *.out *.so *.info matrix_test
	@rm -rf report

# make git m="your message"
git:
	git add .
	git commit -m "$m"
	git push origin develop

.PHONY: all s21_matrix_oop.a s21_matrix_oop.o test gcov_report google style cppcheck Leaks check clean git
