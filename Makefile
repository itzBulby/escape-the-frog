CC = gcc
CFLAGS=-Wall


game : joystick.c led_matrix.c core.c
	$(CC) $(CFLAGS) -lpthread -o game joystick.c led_matrix.c core.c

