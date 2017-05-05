#include "viewWindow.h"
#include "addWindow.h"
#include "graph.h"

using namespace Graph_lib;

int main() {
	try {
		int show_window = 0; //0 = add pic, 1 = view pic

		bool win_next = false;
		bool view_win_next = true;
	  
	  	// Infinite loop until exit via button or OS window close
		while (win_next || view_win_next) {

			if (win_next) {
				show_window = 1;
			}

			if (view_win_next) {
				show_window = 0;
			}
			
			win_next = false;
			view_win_next = false;
			
			if (show_window == 0) {
				addWindow addWin;
				addWin.show();
				win_next = addWin.wait_for_button_view_pic();
			} else if (show_window == 1) {
				viewWindow viewWin;
				viewWin.show();
				view_win_next = viewWin.wait_for_button_new_pic();
			} 
		}
		return 0;
	} catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << "Some exception" << endl;
		return 2;
	}
}