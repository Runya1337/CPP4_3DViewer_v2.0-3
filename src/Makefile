GPP = g++ -Wall -Werror -Wextra -std=c++17
FLAGS = -lm -lcheck
SRC = $(shell find core -name "*.c")
TEST_C = $(shell find test -name "*.c")
MODEL_DIR = Model
TEST_SOURCES = $(MODEL_DIR)/data_3d.cc $(MODEL_DIR)/parser.cc $(MODEL_DIR)/model.cc $(MODEL_DIR)/affine.cc $(MODEL_DIR)/set_centre.cc Tests/tests.cc Controller/controller.cc
TEST_FLAGS = -lgtest -lgtest_main
OS := $(shell uname -s)
QMAKE = qmake
ifeq ($(OS), Linux)
	QMAKE = qmake6
endif

all: clean dist install tests gcov_report dvi

install:
	mkdir -p build
	cd View && $(QMAKE) 3DViewer.pro && make && make clean && rm Makefile
ifeq ($(OS), Darwin)
	mv View/3DViewer.app build
else
	mv View/3DViewer build
endif

uninstall:
	rm -rf build

dist: clean
	tar -czf 3DViewer.tar.gz core View Makefile

dvi:
	open DVI.md

tests: clean
	$(GPP) $(FLAGS) $(TEST_SOURCES) $(TEST_FLAGS) -o all_tests 
	./all_tests

gcov_report: clean
	g++ -std=c++17 -fprofile-arcs -ftest-coverage $(TEST_FLAGS) -o report $(TEST_SOURCES)
	./report
	lcov -c -d . -o coverage.info --ignore-errors mismatch,inconsistent
	genhtml coverage.info --output-directory=res --ignore-errors inconsistent
	open ./res/index.html
	rm -rf *.gcda *.gcno

clean: uninstall
	rm -rf $(shell find . -name "*.o" -o -name "*.out") *.gcno *.gcda *.info report 3DViewer.tar.gz

clang:
	clang-format --style=Google -n $(shell find . -name "*.c" -o -name "*.cpp" -o -name "*.h")
