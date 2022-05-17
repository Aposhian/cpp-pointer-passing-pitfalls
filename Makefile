.PHONY: valgrind
valgrind: programs
	$(foreach executable,$(wildcard bin/*),valgrind --leak-check=full ./$(executable);)

programs: ./src/*.cpp bin_dir
	$(foreach source,$(wildcard *.cpp),g++ -std=c++17 $(source) -o ./bin/$(source).out;)

bin_dir:
	mkdir -p ./bin
