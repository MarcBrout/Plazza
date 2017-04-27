PROJECT_DIR=    ./cipher_manager/			\
		./command_generator			\
		./communication/socket_internet/	\
		./gui/					\
		./logger/ 				\
		./file_scrapper/ 			\
		./ast/					\
		./core/

all:
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

ui:
	@echo "Compile with UI"
	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s UI=yes -C $(c) && ) true

#clean:
#	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true
#
#fclean:
#	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true
#
#re:
#	@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

clean:
	@echo "delete objs"
	@rm -f ./obj/*.o

fclean: clean
	@echo "delete plazza binary"
	@rm -f ./plazza

re: fclean all
