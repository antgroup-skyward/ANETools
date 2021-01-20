CC:=clang
CXX:=clang++
CFLAGS:= -g -Wall -O3 -fsanitize=address
LDFLAGS:= -g -Wall -fsanitize=address -F /System/Library/PrivateFrameworks/ -framework ANECompiler
OBJS:=ANEDisassembler.o util.o wmacho.o
TARGET:=ANEDisassembler

$(TARGET):$(OBJS)
	$(CXX) $^ $(LDFLAGS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)
