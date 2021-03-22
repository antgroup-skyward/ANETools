CC:=g++
CFLAGS:= -g -Wall -O3 -fsanitize=address
LDFLAGS:= -g -fsanitize=address -F /System/Library/PrivateFrameworks/ -framework Espresso
OBJS:=MLModelCToANECompiler.o
TARGET:=MLModelCToANECompiler

$(TARGET):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.mm
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)
