CC=g++
FINALTARGET=test

target:
	$(CC) catch_test_btree.cc -std=c++11 -o test

test: ;"./"$(FINALTARGET)
