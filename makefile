############
###MACROS###

# $(1) : Compiler
# $(2) : Object file to generate
# $(3) : Source file
# $(4) : Additional dependencies
# $(5) : Compiler flags
define COMPILE
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)

endef

# $(1) : Source file
define C2O
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

APP 	 := Game
CCFLAGS  := -Wall -Wextra -pedantic -std=c++20 -I$(shell brew --prefix raylib)/include -Isrc#Flags de compilacion
CFLAGS   := -Wall -pedantic 
CC 	     := g++ -fsanitize=address #Compilador de C++
C		 := gcc #Compilador de C
SANITIZE := -fsanitize=address #flag para detectar fugas de memoria o acceso restringido (en etapa de linker)
MKDIR    := mkdir -p
SRC		 := src
OBJ		 := obj
LIBS	 := -L$(shell brew --prefix raylib)/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

ifdef DEBUG
	CCFLAGS += -g
	CFLAGS += -g
else
	CCFLAGS += -O3
	CFLAGS += -O3
endif

ALLCPPS	 	:= $(shell find src/ -type f -iname *.cpp)
ALLCS		:= $(shell find src/ -type f -iname *.c)
ALLOBJ      := $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
#guarda en subdirs todos los directorios de src/
SUBDIRS	    := $(shell find $(SRC) -type d)
#patsubst me cambia todos los directorios src por obj en objsubdirs
OBJSUBDIRS  := $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))



#comando que explicita que no se lanza siempre
.PHONY: info clean

#Regla principal
#la izquierda se genera a partir de la derecha
$(APP) : $(OBJSUBDIRS) $(ALLOBJ)
	$(CC) -o $(APP) $(ALLOBJ) $(LIBS) $(SANITIZE)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS))))
$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(C),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CFLAGS))))


#info se ejecuta sin depender de nadie
info:
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPS))
	$(info $(ALLCS))
	$(info $(ALLOBJ))

#
$(OBJSUBDIRS):
	$(MKDIR) $@

$(ALLOBJ): | $(OBJSUBDIRS)

clean:
	rm -rf $(OBJ) 
	rm -f $(APP)