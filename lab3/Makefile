
SOURCE_CONTAINERS=Containers.cpp
SOURCE_DE_POP=DE_Population.cpp
SOURCE_DE_STRATS=DE_Strategies.cpp
SOURCE_DRIVER=Driver.cpp
SOURCE_FUNCTIONS=functions.cpp
SOURCE_GA=GA.cpp
SOURCE_GA_POP=GA_Population.cpp
SOURCE_GENE=Gene.cpp
SOURCE_INIPARSER=IniParser.cpp
SOURCE_MAIN=main.cpp
SOURCE_POP=Population.cpp
SOURCE_RESULT=results.cpp
SOURCE_SELECT_STRAT=SelectionStrategy.cpp
SOURCE_TEST=Test.cpp


DRIVER=driver
MAIN=main
TEST=test
DE=DiffEvo
RESULTS=res
GA=GenAlg
INIPARSER=parser
FUNCTIONS=funcs
CONT=Conts
GA_POP=GA_Popul
DE_POP=DE_Popul
POP=Popul
GENE=genes

CC=g++
STD=-std=c++17
FLAGS=-O2 -pipe -msse3

all: $(MAIN) 

$(MAIN): $(DRIVER)
	$(CC) $(SOURCE_MAIN) $(STD) $(FLAGS) *.o -o $(DRIVER)

$(DRIVER): $(INIPARSER) $(TEST) $(GA) $(DE)
	$(CC) -c $(SOURCE_DRIVER) $(STD) $(FLAGS) *.o

$(TEST): $(FUNCTIONS) $(RESULTS)
	$(CC) -c $(SOURCE_TEST) $(STD) $(FLAGS) *.o

$(INIPARSER):
	$(CC) -c $(SOURCE_INIPARSER) $(STD) $(FLAGS)

$(FUNCTIONS):
	$(CC) -c $(SOURCE_FUNCTIONS) $(STD) $(FLAGS)

$(GA): $(GA_POP)
	$(CC) -c $(SOURCE_GA) $(STD) $(FLAGS)

$(GA_POP): $(POP)
	$(CC) -c $(SOURCE_GA_POP) $(STD) $(FLAGS)

$(DE): $(DE_POP)
	$(CC) -c $(SOURCE_DE_STRATS) $(STD) $(FLAGS)

$(DE_POP): $(POP)
	$(CC) -c $(SOURCE_DE_POP) $(STD) $(FLAGS)

$(POP): $(GENE)
	$(CC) -c $(SOURCE_POP) $(STD) $(FLAGS)

$(GENE): $(CONT)
	$(CC) -c $(SOURCE_GENE) $(STD) $(FLAGS)

$(CONT):
	$(CC) -c $(SOURCE_CONTAINERS) $(STD) $(FLAGS)

$(RESULTS):
	$(CC) -c $(SOURCE_RESULT) $(STD) $(FLAGS)

clean: 
	rm -f $(DRIVER) *.h.gch *.hpp.gch *.o *.csv

