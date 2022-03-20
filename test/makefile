include_path := ../include

VPATH := $(include_path)
CC := g++
CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -O -ggdb \
            -std=c++17 -I$(include_path) \
						-fsanitize=address,leak
LDLIBS := -lgtest -lgtest_main -lpthread 

targets := bigint_test \
           fenwick_tree_test \
					 matrix_test \
					 modint_test \
      		 union_find_test \
					 trie_test \
					 fft_test \
					 string_test \
					 AC_test \
					 segtree_test \
					 sparse_table_test \


default: $(targets)

test: $(targets)
	for target in `echo $(targets) | sed s/.exe//g`; do	./"$$target"; done

.PHONY: clean
clean:
	-rm -f $(targets) $(objects)
