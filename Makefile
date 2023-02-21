.PHONY: valgrind
valgrind: programs
	$(foreach executable,$(wildcard bin/*),valgrind --leak-check=full ./$(executable);)

programs: ./src/*.cpp bin_dir
	$(foreach source,$(wildcard */**.cpp),g++ -std=c++20 $(source) -o ./bin/$(notdir $(source)).out;)

bin_dir:
	mkdir -p ./bin
