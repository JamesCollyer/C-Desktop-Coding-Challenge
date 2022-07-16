
FLAGS = `wx-config --cxxflags --libs std`
COMPILER = g++

app: cMain.cpp cMain.h cApp.cpp cApp.h
	$(COMPILER) cMain.cpp cMain.h cApp.cpp cApp.h testcases.cpp testcases.h $(FLAGS) -o Challenge_Linux

clean:
	rm Challenge_Linux user_program.cpp user_exe result.txt

