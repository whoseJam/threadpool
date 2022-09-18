
SUB_DIR:= ./thpool ./DAG ./sayHello

all:rDAG rHello
	@echo mission completed

rDAG:DAG.o thpool.o
	g++ ./build/DAG.o ./build/thpool.o -o rDAG -lpthread

rHello:Hello.o thpool.o
	g++ ./build/Hello.o ./build/thpool.o -o rHello -lpthread

DAG.o:
	$(MAKE) -C ./DAG

thpool.o:
	$(MAKE) -C ./thpool

Hello.o:
	$(MAKE) -C ./sayHello

clean:
	rm *.o