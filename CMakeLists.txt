project(dict)

add_library(dict
    src/dict.c
    src/primes.c
    src/dict_entry.c
    src/none.c
)


add_executable(
    test_dict
    src/test_dict.c
)
target_link_libraries(test_dict dict)

#add_iexecutable(
#    markov
#:  arr.obj
    # tokenise.obj
    #  options.obj

    #markov: src/apps/markov/markov.c $(LIBDICT_SRC) $(MARKOV_SRC)
#	$(CC) $(CFLAGS) src/apps/markov/markov.c $(LIBDICT_SRC) $(MARKOV_SRC) -o $@
