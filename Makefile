# ============================================================
# Makefile — Inheritance & Polymorphism lab
# Targets:
#   make            build the program (MainProgram.cpp -> program)
#   make test       build the test binary
#   make run        run the program
#   make test_1 ... test_6   run one test group (partial credit)
#   make clean      remove build artifacts
# ============================================================

CXX      := g++
CXXFLAGS := -Wall --std=c++17

PROG     := program
TEST_BIN := test_bin

# ---- Build the student/teacher program ----
all: $(PROG)

$(PROG): MainProgram.cpp
	$(CXX) $(CXXFLAGS) MainProgram.cpp -o $(PROG)

run: $(PROG)
	./$(PROG)

# ---- Build the test binary ----
# test.cpp #includes MainProgram.cpp, so only test.cpp + Catch2 are compiled.
$(TEST_BIN): test.cpp MainProgram.cpp catch_amalgamated.cpp
	$(CXX) $(CXXFLAGS) test.cpp catch_amalgamated.cpp -o $(TEST_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

# ---- Per-group targets for partial credit ----
test_1: $(TEST_BIN)
	./$(TEST_BIN) [t1]

test_2: $(TEST_BIN)
	./$(TEST_BIN) [t2]

test_3: $(TEST_BIN)
	./$(TEST_BIN) [t3]

test_4: $(TEST_BIN)
	./$(TEST_BIN) [t4]

test_5: $(TEST_BIN)
	./$(TEST_BIN) [t5]

test_6: $(TEST_BIN)
	./$(TEST_BIN) [t6]

clean:
	rm -f $(PROG) $(TEST_BIN)

.PHONY: all run test test_1 test_2 test_3 test_4 test_5 test_6 clean
