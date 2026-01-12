# Resource to learn Make: https://www.gnu.org/software/make/manual/html_node/index.html

CC:=gcc
CFLAGS:=-g
# To turn off warnings change line above to "CFLAGS:=-g -w"
BIN_NAME:=53library
SRC_DIR:=src
INCLUDE_DIR:=include
BIN_DIR:=bin
PRG_SUFFIX:=.out

# These are called rules. Rules have targets (what to make), and prerequisites (what needs to exist).
# Make won't build a target if it's prerequisites haven't changed; it's smart enough not to re-do it's work. The syntax for rules is:
# target(s): prerequisite(s)
# \trecipe (how to make the target)
# ...
# The tab character is important (no spaces), and the recipe is a series of shell command(s)
# all: clean setup sync p1test_main p2test_main linkedlisttest_main 53library
all: clean setup p1test_main p2test_main linkedlisttest_main 53library
	
53library: src/hw2.c  src/helpers2.c src/linkedlist.c src/53library.c
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $(SRC_DIR)/53library.c  $(SRC_DIR)/linkedlist.c $(SRC_DIR)/helpers2.c $(SRC_DIR)/hw2.c -o $(BIN_DIR)/53library

#compile all the main files
p1test_main: setup src/hw2.c src/helpers2.c src/linkedlist.c tests/p1test_main.c
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $(SRC_DIR)/helpers2.c $(SRC_DIR)/linkedlist.c $(SRC_DIR)/hw2.c tests/p1test_main.c -o $(BIN_DIR)/p1test_main

p2test_main: setup src/hw2.c src/helpers2.c src/linkedlist.c tests/p2test_main.c
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $(SRC_DIR)/linkedlist.c $(SRC_DIR)/helpers2.c $(SRC_DIR)/hw2.c tests/p2test_main.c -o $(BIN_DIR)/p2test_main

linkedlisttest_main: setup src/hw2.c src/helpers2.c src/linkedlist.c tests/linkedlisttest_main.c
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $(SRC_DIR)/linkedlist.c $(SRC_DIR)/helpers2.c $(SRC_DIR)/hw2.c tests/linkedlisttest_main.c -o $(BIN_DIR)/linkedlisttest_main

all_tests: setup tests/all_tests.c
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) $(SRC_DIR)/linkedlist.c $(SRC_DIR)/helpers2.c $(SRC_DIR)/hw2.c tests/all_tests.c -o $(BIN_DIR)/all_tests

setup:
	@mkdir -p $(BIN_DIR)

sync: 
	rsync -av --files-from=sync_list.txt . eeleyes@10.147.17.130:~/school/ICS53/hw/hw2/

remote_test: sync
	ssh -t eeleyes@10.147.17.130 "cd ~/school/ICS53/hw/hw2; make all_tests && valgrind --leak-check=yes ./bin/all_tests"

# Standard (ish) rule to clean out files we'd like to re-generate
clean:
	rm -rf $(BIN_DIR) .cache

# By default, make will assume each target is a file. This means that it won't actually run the clean target if a file called ```clean``` exists.
# The following special target overrides this behavior; it's prerequisites are always run.
.PHONY: clean
