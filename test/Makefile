CXX=g++-4.9
CXXFLAGS=-std=c++11 -I../lib
COMMON_FILES=intf.cc

all: spinlock_test condvar_test sem_test mutex_test recursive_mutex_test

condvar_test: condvar_test.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FILES) condvar_test.cc -o condvar_test

sem_test: sem_test.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FILES) sem_test.cc -o sem_test

spinlock_test: spinlock_test.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FILES) spinlock_test.cc -o spinlock_test

mutex_test: mutex_test.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FILES) mutex_test.cc -o mutex_test

recursive_mutex_test: recursive_mutex_test.cc
	$(CXX) $(CXXFLAGS) $(COMMON_FILES) recursive_mutex_test.cc -o recursive_mutex_test

.PHONY: clean test
clean:
	rm -f spinlock_test condvar_test sem_test mutex_test recursive_mutex_test

test: all
	./spinlock_test
	./condvar_test
	./sem_test
	./mutex_test
	./recursive_mutex_test
