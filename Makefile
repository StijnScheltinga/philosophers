SOURCES	=		main.c set_data.c utils.c create_threads.c
SRC_DIR	=		src
BUILD	=		build
OBJECTS	=		$(addprefix $(BUILD)/, $(SOURCES:.c=.o))
NAME	=		philo	
FLAGS	=		
CC		=		gcc
INCLUDE	=		-I inc/philo.h
PTHREAD	=		-lpthread

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(flags) -o $(NAME) $(OBJECTS) $(PTHREAD)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	gcc -g $(FLAGS) $(INCLUDE) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -rf $(OBJECTS) $(BUILD)

fclean:
	rm -rf $(OBJECTS) $(NAME) $(BUILD)

re: fclean all