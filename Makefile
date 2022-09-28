CXX = g++

CXXFLAGS = -DLOCAL \
					 -std=c++20 \

# debug
CXXFLAGS += -ggdb \
            -D_GLIBCXX_DEBUG \
					  -D_GLIBCXX_DEBUG_PEDANTIC \

# warnings
CXXFLAGS += -Wall \
					  -Wextra \
					  -Wshadow \
					  -Wshadow \
					  -Wformat=2 \
					  -Wduplicated-cond \
					  -Wfloat-equal \
					  -Wconversion \
					  -Wlogical-op \
					  -pedantic \

# sanitizers
CXXFLAGS += -fsanitize=address \
					  -fsanitize=undefined \
					  -fsanitize=float-divide-by-zero \
					  -fno-sanitize-recover=all \
					  -fstack-protector-all
					  -D_FORTIFY_SOURCE=2 \

clean:
	-rm -rf [A-Za-z]
