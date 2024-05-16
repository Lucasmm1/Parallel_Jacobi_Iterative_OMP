#######################################################
# - Caíque Honorio Cardoso 			- NºUSP: 8910222  #
# - Erika Hortência Pereira Cardoso - NºUSP: 10696830 #
# - Gabriel Cazzini Cardoso 		- NºUSP: 12547771 #
# - Lucas Machado Marinho 			- NºUSP: 11916645 #
#######################################################

CC = gcc
CFLAGS = -fopenmp
SEQ_SRC = jacobiseq.c
PAR_SRC = jacobipar.c
SEQ_EXEC = jacobiseq
PAR_EXEC = jacobipar

all: $(SEQ_EXEC) $(PAR_EXEC)

$(SEQ_EXEC): $(SEQ_SRC)
	$(CC) $(CFLAGS) $(SEQ_SRC) -o $(SEQ_EXEC) -lm

$(PAR_EXEC): $(PAR_SRC)
	$(CC) $(CFLAGS) $(PAR_SRC) -o $(PAR_EXEC) -lm

.PHONY: clean makerun

clean:
	rm -f $(SEQ_EXEC) $(PAR_EXEC)

makerun:
	@read -p "Digite 'jacobiseq' ou 'jacobipar': " exec; \
	if [ $$exec = "jacobiseq" ]; then \
		read -p "Digite N: " N; \
		read -p "Digite a seed: " seed; \
		./$$exec $$N $$seed; \
	elif [ $$exec = "jacobipar" ]; then \
		read -p "Digite N: " N; \
		read -p "Digite T: " T; \
		read -p "Digite a seed: " seed; \
		./$$exec $$N $$T $$seed; \
	else \
		echo "Opcao invalida"; \
	fi
