SOURCES	=		main.c set_struct.c utils.c
SRC_DIR	=		src
BUILD	=		build
OBJECTS	=		$(addprefix $(BUILD)/, $(SOURCES:.c=.o))
NAME	=		philo	
FLAGS	=		-Wall -Werror -Wextra
CC		=		gcc
INCLUDE	=		-I inc/philo.h

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(flags) -o $(NAME) $(OBJECTS)

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	gcc -g $(FLAGS) $(INCLUDE) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -rf $(OBJECTS) $(BUILD)

fclean:
	rm -rf $(OBJECTS) $(NAME) $(BUILD)

re: fclean all