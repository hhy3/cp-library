CXX = g++
CXXFLAGS = -ggdb -DLOCAL -std=c++20 -Wall -Wextra -Wshadow -Wshadow -Wformat=2 -Wduplicated-cond -pedantic -Wfloat-equal -Wconversion -Wlogical-op -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2
LDFLAGS = -lfmt

clean:
	-rm -rf [A-Za-z]
