cc = gcc
c_flags = -std=gnu11 -O2 -Werror -Wall -o $(exe)
main = all_tests
aux = CuTest test_filter
c_files = $(main).c $(aux:%=%.c)
h_files = $(aux:%=%.h)
build_dir = ../build
exe = $(build_dir)/$(main)

.PHONY : all clean

all : $(exe)

$(exe) : $(c_files) $(h_files)
	$(cc) $(c_flags) $(c_files)

clean :
	rm -f $(exe)

run :
	$(exe)
