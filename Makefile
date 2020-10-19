vpath %.h ./Common ./Algorithms ./Clustering/ ./Structures
vpath %.cpp ./Common ./Algorithms ./Clustering/ ./Structures .
vpath %.o ./Objects

CC =			g++
FLAGS = 		-c
OBJS_CLSTRNG =	algorithm.o Assignment.o Cluster.o Config.o Silhouette.o UtilsCluster.o
OBJS_CMMN =		bucket.o CmdArgumentsReader.o dataset.o Distance.o hashFuncs.o image.o PriorityQueue.o Utils.o
OBJS_STRCT =	HyperCube.o lsh.o
OBJS_ALG = 		AproxNN.o ExactNN.o RangeSearch.o
ALL_OBJS :=		$(wildcard Objects/*.o) 
OBJS_DIR =		./Objects
EXECS =			lsh cube cluster

all: $(EXECS)

lsh: lsh_main.o $(OBJS_CMMN) $(OBJS_STRCT) $(OBJS_ALG)
	$(CC) $(OBJS_DIR)/* -o $@
	rm $(OBJS_DIR)/lsh_main.o

cube: cube_main.o $(OBJS_CMMN) $(OBJS_STRCT) $(OBJS_ALG) 
	$(CC) $(OBJS_DIR)/* -o $@
	rm $(OBJS_DIR)/cube_main.o

cluster: cluster_main.o $(OBJS_CMMN) $(OBJS_STRCT) $(OBJS_ALG) $(OBJS_CLSTRNG)
	$(CC) $(OBJS_DIR)/* -o $@
	rm $(OBJS_DIR)/cluster_main.o

%.o: %.cpp %.h
	$(CC) $(FLAGS) $< -o $(OBJS_DIR)/$@

%.o: %.cpp
	$(CC) $(FLAGS) $< -o $(OBJS_DIR)/$@

clean:
	rm -rf $(ALL_OBJS) $(EXECS)