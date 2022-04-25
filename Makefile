CFLAGS = -std=c99 -g -Wall -Wshadow -Wvla -pedantic -Werror
GCCALL = gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic
GCC = gcc $(CFLAGS)
EXEC = pa5
OBJS =  pa5.o build_graph.o struct.o write_output.o traverse_graph.o helper.o
HOBJS = build_graph.h struct.h write_output.h traverse_graph.h helper.h
VALGRIND = valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --verbose

$(EXEC): $(OBJS) $(HOBJS)
	$(GCC) $(OBJS) -o $(EXEC)

45: $(EXEC)
	mkdir outputs
	./$(EXEC) examples/4_5.b outputs/4_5.t outputs/4_5.f outputs/4_5.p
	diff examples/4_5.t outputs/4_5.t
	diff examples/4_5.f outputs/4_5.f

77: $(EXEC)
	mkdir outputs
	./$(EXEC) examples/7_7.b outputs/7_7.t outputs/7_7.f outputs/7_7.p
	diff examples/7_7.t outputs/7_7.t
	diff examples/7_7.f outputs/7_7.f

test: $(EXEC)
	mkdir outputs
	./$(EXEC) examples/4_5.b outputs/4_5.t outputs/4_5.f outputs/4_5.p
	diff examples/4_5.t outputs/4_5.t
	diff examples/4_5.f outputs/4_5.f
	./$(EXEC) examples/5_4.b outputs/5_4.t outputs/5_4.f outputs/5_4.p
	diff examples/5_4.t outputs/5_4.t
	diff examples/5_4.f outputs/5_4.f
	./$(EXEC) examples/5_5.b outputs/5_5.t outputs/5_5.f outputs/5_5.p
	diff examples/5_5.t outputs/5_5.t
	diff examples/5_5.f outputs/5_5.f
	./$(EXEC) examples/7_7.b outputs/7_7.t outputs/7_7.f outputs/7_7.p
	diff examples/7_7.t outputs/7_7.t
	diff examples/7_7.f outputs/7_7.f

memory: $(EXEC)
	mkdir moutputs
	$(VALGRIND) ./$(EXEC) examples/4_5.b moutputs/4_5.t moutputs/4_5.f moutputs/4_5.p
	$(VALGRIND) ./$(EXEC) examples/5_4.b moutputs/5_4.t moutputs/5_4.f moutputs/5_4.p
	$(VALGRIND) ./$(EXEC) examples/5_5.b moutputs/5_5.t moutputs/5_5.f moutputs/5_5.p
	$(VALGRIND) ./$(EXEC) examples/7_7.b moutputs/7_7.t moutputs/7_7.f moutputs/7_7.p

clean: 
	/bin/rm -f $(EXEC)
	/bin/rm -f *.o
	/bin/rm -rf outputs moutputs