#ifndef ADDWINDOW_H_
#define ADDWINDOW_H_

#include "std_lib_facilities_4.h"
#include "window.h"
#include "graph.h"
#include "gui.h"

using namespace Graph_lib;

struct addWindow : Graph_lib::Window {
	public:
		addWindow():
			Window(Point(0,0),600,300,"AggieSnap | Add Pictures"),
			view_button_pushed(false),
			error(4),
			Url(Point(100,0),200,25,"Filename/URL"),
			tag1(Point(100,50),200,25,"Tag 1"),
			tag2(Point(100,100),200,25,"Tag 2"),
			tag3(Point(100,150),200,25,"Tag 3"),
			tag4(Point(100,200),200,25,"Tag 4"),
			tag5(Point(100,250),200,25,"Tag 5"),

			button_add_pic(Point(350,0),200,25,"Add picture to database",cb_add_pic),
			button_view_pic(Point(350,50),200,25,"Browse pictures",cb_view_pic),
			button_quit(Point(350,100),200,25,"Quit AggieSnap",cb_quit)
			{	
				// Attach buttons		
				attach(button_add_pic);
				attach(button_view_pic);
				attach(button_quit);
				
				// Attach in boxes
				attach(Url);
				attach(tag1);
				attach(tag2);
				attach(tag3);
				attach(tag4);
				attach(tag5);

				// Default empty message
				msg = new Text(Point(40,180),"");
				attach(*msg);
			}
			
			bool wait_for_button_view_pic();
			
	private:
		static void cb_add_pic(Address,Address); 
		static void cb_view_pic(Address,Address);
		static void cb_quit(Address,Address);
		void displayError(int);
		
		void add_pic();
		void view_pic();
		void quit();
		
		In_box Url,tag1,tag2,tag3,tag4,tag5;
		Button button_add_pic,button_view_pic,button_quit;
		string output, first_tag, second_tag, third_tag, fourth_tag, fifth_tag;
		bool view_button_pushed;
		Text *msg;
		int error;
};	
#endif