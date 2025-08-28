CC = gcc

CFLAGS = -Wall -Isrc

EXECUTABLE = projeto_final


SRCS = src/main.c \
       src/utils/utils.c \
       src/vetor_binario/vetor_binario.c \
       src/arvore_bst/arvore_bst.c \
       src/arvore_avl/arvore_avl.c \
       src/arvore_avl_frequencia/arvore_avl_frequencia.c


OBJS = $(SRCS:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(EXECUTABLE)

clean:
	rm -f $(OBJS) $(EXECUTABLE)

.PHONY: all clean run