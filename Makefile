# Nom de l'exécutable
TARGET = main
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Fichiers source
SRCS = main.c logic.c board.c cell.c bot.c
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Génération de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
