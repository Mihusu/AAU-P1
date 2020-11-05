cc = gcc
c_flags = -std=gnu11 -O2 -Werror -Wall -iquote src -o $(exe)
main = all_tests
aux = test/CuTest test/filter_test test/format_test test/read_test src/filter
c_files = test/$(main).c $(aux:%=%.c)
h_files = $(aux:%=%.h)
build_dir = build
exe = $(build_dir)/$(main)
#exe = $(main)

.PHONY : all clean test

all : $(exe)

$(exe) : $(c_files) $(h_files)
	$(cc) $(c_flags) $(c_files)

clean :
	rm -f $(exe)

test :
	$(exe)
