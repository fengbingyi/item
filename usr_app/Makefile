CC := gcc
CFLAGS := -c -o
TARGET ?= app
OBJS += usr_app.o
OBJS += menu.o
OBJS += client.o
OBJS += reg.o
OBJS += login.o
OBJS += manager_function.o
OBJS += usr_function.o
OBJS += applib.o

all:$(OBJS)
	$(CC)   $^ -o $(TARGET)
	$(CC) server_test.c -o t_server 

%.o:%.c
	$(CC) $(CFLAGS) $@ $< 

clean:
	rm *.o $(TARGET)


