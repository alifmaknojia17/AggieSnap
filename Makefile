all:
	@echo "Compiling AggieSnap source files..."
	-@g++-4.7 -std=c++11 *cpp -lfltk -lfltk_images -o aggiesnap
clear:
	@echo "Resetting db, counter, and images folder..."
	-@rm -rf images/*; rm db; touch db; rm counter; echo "1" >> counter;
.PHONY: test
