CC       := gcc
CFLAGS   := -std=c11 -O2 -Wall -Wextra -pedantic -D_POSIX_C_SOURCE=200809L
LDFLAGS  := 
SRC      := main.c sensors.c actuators.c buttons.c watering_logic.c
OBJ      := $(SRC:.c=.o)
TARGET   := spws

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c config.h types.h sensors.h actuators.h buttons.h watering_logic.h
sensors.o: sensors.c sensors.h types.h config.h
actuators.o: actuators.c actuators.h types.h config.h
buttons.o: buttons.c buttons.h
watering_logic.o: watering_logic.c watering_logic.h types.h config.h actuators.h sensors.h

clean:
	rm -f $(OBJ) $(TARGET)
