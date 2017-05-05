#ifndef VIEWWINDOW_H_
#define VIEWWINDOW_H_

#include "window.h"
#include "graph.h"
#include "gui.h"
#include "global.h"

using namespace Graph_lib;

struct viewWindow : Graph_lib::Window {
	public:
		viewWindow() :
			Window(Point(0,0),830,700,"AggieSnap | Browse Pictures"),
			new_button_pushed(false),
			next_button_pushed(false),
			previous_button_pushed(false),
			search_button_pushed(false),
			reset_search_button_pushed(false),
			update_tags_button_pushed(false),
			cycleVals(defaultImages()),
			imgObj(),
			imgLoc(),
			//outbox
			tag1(Point(75, 600), 90, 25, "Tag 1"),
			tag2(Point(225, 600), 90, 25, "Tag 2"),
			tag3(Point(375, 600), 90, 25, "Tag 3"),
			tag4(Point(525, 600), 90, 25, "Tag 4"),
			tag5(Point(675, 600), 90, 25, "Tag 5"),
			//inbox
			search(Point(340,0), 100, 25, "Search Tags"),
			// Buttons
			button_next(Point(700, 100), 100, 450, "Next", cb_next),
			button_previous(Point(25, 100), 100, 450, "Previous", cb_previous),
			button_new_pic(Point(350, 560), 125, 25, "Add a Picture", cb_new_pic),
			button_reset_search(Point(380,40),120,25,"Reset Search",cb_reset_tag_search),
			button_tag_search(Point(450, 0), 70, 25, "Search", cb_tag_search),
			button_quit(Point(690,20),120,25,"Quit AggieSnap",cb_quit),
			button_update_tags(Point(350,650),120,25,"Update Tags",cb_update_tags) {	
				// Attach buttons	
				attach(button_next);
				attach(button_previous);
				attach(button_new_pic);
				attach(button_tag_search);
				attach(button_reset_search);
				attach(button_quit);
				attach(button_update_tags);
				
				// Attach outboxes/inboxes
				attach(tag1);
				attach(tag2);
				attach(tag3);
				attach(tag4);
				attach(tag5);
				attach(search);

				// If user has images in DB and hasn't pushed previous or next yet, display the 1st image in the database
				if ((!next_button_pushed || !previous_button_pushed) && currentCount() != 1) {
					imgObj = getImage(1);
					imgLoc = "images/1." + imgObj.getExtension();
					img = new Image(Point(140,150), imgLoc);

					// Crop image
					img->set_mask(Point(0,0),550,400);

					// Get image name
					name = new Text(Point(140,100), imgObj.getShortName() + "." + imgObj.getExtension());
					name->set_font_size(25);

					// Get image date and show whether it was added or downloaded
					time_t date = imgObj.getDate();

					if (imgObj.getType() == FILE_LOCAL) {
						datastring = "Added to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t 1 / " + to_string(cycleVals.size());
					} else {
						datastring = "Downloaded to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t 1 / " + to_string(cycleVals.size());
					}

					data = new Text(Point(140,125), datastring);

					// Update tag information
					tag1.put(to_string(imgObj.getTag(1)));
					tag2.put(to_string(imgObj.getTag(2)));
					tag3.put(to_string(imgObj.getTag(3)));
					tag4.put(to_string(imgObj.getTag(4)));
					tag5.put(to_string(imgObj.getTag(5)));

					// Attach image, name, and data
					attach(*img);
					attach(*name);
					attach(*data);
					// If user has no images in DB
				} else {
					// Set null/default values of image, name, data, and tags
					img = new Image(Point(300,275), "default.jpg");

					name = new Text(Point(140,100), "");
					name->set_font_size(25);

					data = new Text(Point(140,125), "");

					tag1.put("");
					tag2.put("");
					tag3.put("");
					tag4.put("");
					tag5.put("");

					// Attach image, name, and data
					attach(*img);
					attach(*name);
					attach(*data);
				}
			}
		
		bool wait_for_button_new_pic();
		bool wait_for_button_next_pic();
		bool wait_for_button_previous_pic();
		bool wait_for_reset_search_button();
		bool wait_for_button_update_tags();
		int index = 0;
		
	private:
		// Call back functions for buttons
		static void cb_next(Address, Address);
		static void cb_previous(Address, Address);
		static void cb_new_pic(Address, Address);
		static void cb_tag_search(Address, Address);
		static void cb_reset_tag_search(Address, Address);
		static void cb_quit(Address, Address);
		static void cb_update_tags(Address, Address);
		
		// Respective functions for call backs
		void next();
		void previous();
		void new_pic();
		void tag_search();
		void reset_tag_search();
		void redrawUpdate();
		void quit();
		void update_tags();
		
		
		In_box search;
		In_box tag1, tag2, tag3, tag4, tag5;
		Button button_next, button_previous, button_new_pic, button_tag_search, button_reset_search, button_quit, button_update_tags;
		string tags;
		imageOutput imgObj;
		Image *img;
		string imgLoc, datastring;
		Text *name, *data, *changes_saved;
		vector<int> cycleVals;
		bool new_button_pushed;
		bool next_button_pushed;
		bool previous_button_pushed;
		bool search_button_pushed;
		bool reset_search_button_pushed;
		bool update_tags_button_pushed;
};

#endif