CC:=clang++
CFLAGS:= -g -Wall -O3 -fsanitize=address
LDFLAGS:= -g -Wall -fsanitize=address -F /System/Library/PrivateFrameworks/ -framework ANECompiler -framework CoreFoundation
OBJS:=ANECompiler.o
TARGET:=ANECompiler

$(TARGET):$(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

%.o:%.mm
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) $(OBJS)
