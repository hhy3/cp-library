include_path := ../include

VPATH := $(include_path)
CC := g++
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -O -ggdb -std=c++17 -I$(include_path) 
LDLIBS := -lgtest -lgtest_main -lpthread 

targets := fenwick_tree_test \
      		 union_find_test \
			     LIS_test \

default: $(targets)

test: $(targets)
	for target in `echo $(targets) | sed s/.exe//g`; do	./"$$target"; done

.PHONY: clean
clean:
	-rm -f $(targets) $(objects)
