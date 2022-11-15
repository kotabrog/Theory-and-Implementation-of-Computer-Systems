NAME := JackAnalyzer
SOURCES_FOLDER = src/
SOURCES =	main.cpp \
			JackTokenizer.cpp \
			CompilationEngine.cpp \
			SymbolTable.cpp \

SOURCES_PREFIXED = $(addprefix $(SOURCES_FOLDER), $(SOURCES))

INCLUDES_FOLDER = inc/
INCLUDES =	JackAnalyzer.hpp \
			Type.hpp \
			JackTokenizer.hpp \
			CompilationEngine.hpp \
			SymbolTable.hpp \

INCLUDES_PREFIXED = $(addprefix $(INCLUDES_FOLDER), $(INCLUDES))

OBJECTS_FOLDER = obj/
OBJECT = $(SOURCES:.cpp=.o)
OBJECTS = $(addprefix $(OBJECTS_FOLDER), $(OBJECT))
DEPENDENCIES = $(OBJECTS:.o=.d)

CXX := g++
CXXFLAGS := -Wall -Wextra -Werror

$(OBJECTS_FOLDER)%.o: $(SOURCES_FOLDER)%.cpp
	@mkdir -p $(OBJECTS_FOLDER)
	@echo "Compiling : $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDES_FOLDER)

$(NAME): $(OBJECTS)
	@echo "Create    : $(NAME)"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)

-include $(DEPENDENCIES)

clean:
	@rm -rf $(OBJECTS_FOLDER)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re format
