PROJECT_DIR=    ./cipher_manager/			\
		./command_generator			\
		./communication/socket_internet/	\
		./gui/					\
		./core/					\
		./logger/ 				\
		./file_scrapper/ 			\
		./ast/

all:
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true
