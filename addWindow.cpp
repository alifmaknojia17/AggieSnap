#include "addWindow.h"
#include "Input.h"

// Button callback functions ////////
void addWindow::cb_add_pic(Address,Address pw)
{
	reference_to<addWindow>(pw).add_pic() ;
}

void addWindow::cb_view_pic(Address,Address pw)
{
	reference_to<addWindow>(pw).view_pic() ;
}

void addWindow::cb_quit(Address,Address pw)
{
	reference_to<addWindow>(pw).quit() ;
}
/////////////////////////////////////

// Button callback actions ////////

// Add picture to db
void addWindow::add_pic()
{
	// Image object is created
	imageInput image;
	
	// Send image values to acceptInput function for processing and record any errors
	error = image.acceptInput(Url.get_string(), vector<string> {tag1.get_string(), tag2.get_string(), tag3.get_string(), tag4.get_string(), tag5.get_string()});

	// Display error codes
	displayError(error);
}

// Display error message depending on code received
void addWindow::displayError(int errorNum) {
	string msgContent;

	// Detach previous error message
	detach(*msg);

	if (errorNum == 0) {
		msg = new Text(Point(320,200),"Successfully added picture!");
		msg->set_color(Color::dark_green);
		msg->set_font_size(15);

		// Reset input fields
		Url.put("");
		tag1.put("");
		tag2.put("");
		tag3.put("");
		tag4.put("");
		tag5.put("");

	} else {
		if (errorNum == 1) {
			msg = new Text(Point(320, 200), "Invalid image extension, please try again!");
		} else if (errorNum == 2) {
			msg = new Text(Point(320, 200), "Invalid Url, try again!");
		} else if (errorNum == 3) {
			msg = new Text(Point(320, 200), "Invalid Local image, try again!");
		} else if (errorNum == 4) {
			msg = new Text(Point(320, 200), "Unknown Error, please try again!");
		}
		msg->set_color(Color::red);
		msg->set_font_size(15);
	}

	// Attach and redraw
	attach(*msg);
	Fl::redraw();
}

// Done adding pictures button
void addWindow::view_pic() {
	hide();
	view_button_pushed = true;
}

// Wait until user hits browse pictures
bool addWindow::wait_for_button_view_pic()
{
    show();
    view_button_pushed = false;
    Fl::run();
    return view_button_pushed;
}

// Quit AggieSnap
void addWindow::quit() {
	exit(EXIT_SUCCESS);
}