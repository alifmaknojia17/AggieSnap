#include "viewWindow.h"

// Buttons
void viewWindow::cb_next(Address, Address pw) {
	reference_to<viewWindow>(pw).next();
}

void viewWindow::cb_previous(Address, Address pw) {
	reference_to<viewWindow>(pw).previous();
}

void viewWindow::cb_new_pic(Address,Address pw) {
	reference_to<viewWindow>(pw).new_pic();
}

void viewWindow::cb_tag_search(Address,Address pw) {
	reference_to<viewWindow>(pw).tag_search();
}

void viewWindow::cb_reset_tag_search(Address,Address pw) {
	reference_to<viewWindow>(pw).reset_tag_search();
}

void viewWindow::cb_quit(Address,Address pw) {
	reference_to<viewWindow>(pw).quit();
}

void viewWindow::cb_update_tags(Address,Address pw) {
	reference_to<viewWindow>(pw).update_tags();
}

// Next button
void viewWindow::next() {
	// If there are pictures to cycle through
	if (cycleVals.size() != 0) {
		// Increase picture index by one
		++index;

		// Start from beginning
		if (index>cycleVals.size()-1) {
			index = 0;
		}

		// Redraw update image and image info
		redrawUpdate();

		next_button_pushed = true;
	}
}

// Previous button
void viewWindow::previous() {
	// If there are pictures to cycle through
	if (cycleVals.size() != 0) {
		// Decrease picture index by one
		--index;

		// If out of range, start from end of cycleVals
		if (index == -1) {
			index = cycleVals.size()-1;
		}

		// Redraw update image and image info
		redrawUpdate();

		previous_button_pushed = true;
	}
}

// Add pictures
void viewWindow::new_pic() {
	
	// Go to add picture screen
	hide();
	new_button_pushed = true;
}

// Filter pictures by tag
void viewWindow::tag_search() {
	tags = strtolower(search.get_string());
	cycleVals = searchImages(tags);
	index = 0;

	// If no matches found, display no matches found image or else display first image of matches
	if (cycleVals.size() == 0) {
		// Detach previous image, name, data, and saved_tags
		detach(*img);
		detach(*name);
		detach(*data);
		detach(*changes_saved);

		img = new Image(Point(300,275), "nomatches.jpg");

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
	} else {
		// Redraw update image and image info
		redrawUpdate();
	}

	search_button_pushed = true;

	// Redraw GUI
	Fl::redraw();
}

// Reset tag search input and cycleVals
void viewWindow::reset_tag_search() {
	// Clear search box
	search.put("");

	// Cycle through default images
	cycleVals = defaultImages();

	// If user has images in DB and hasn't pushed previous or next yet, display the 1st image in the database
	if (currentCount() != 1) {
		// Redraw update image and image info
		redrawUpdate();
	} else {
		// Detach previous image, name, data, and saved_tags
		detach(*img);
		detach(*name);
		detach(*data);
		detach(*changes_saved);

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

	search_button_pushed = false;

	// Redraw GUI
	Fl::redraw();
}

// Quit window
void viewWindow::quit() {
	exit(EXIT_SUCCESS);
}

// Update tags
void viewWindow::update_tags() {
	if (cycleVals.size() != 0) {
		detach(*changes_saved);

		// Update tags
		updateTags(index+1, {tag1.get_string(), tag2.get_string(), tag3.get_string(), tag4.get_string(), tag5.get_string()});

		update_tags_button_pushed = true;
		changes_saved = new Text(Point(335,640),"Changes Saved Successfully");
		changes_saved->set_font_size(15);
		changes_saved->set_color(Color::dark_green);

		attach(*changes_saved);

		// Redraw GUI
		Fl::redraw();
	}
}

// Listener boolean values
bool viewWindow::wait_for_button_new_pic() {
    show();
    new_button_pushed = false;
    Fl::run();
    return new_button_pushed;
}


bool viewWindow::wait_for_button_next_pic() {
    next_button_pushed = false;
    return next_button_pushed;
}

bool viewWindow::wait_for_button_previous_pic() {
    previous_button_pushed = false;
    return previous_button_pushed;
}

bool viewWindow::wait_for_reset_search_button() {
	reset_search_button_pushed = false;
	return reset_search_button_pushed;
}

bool viewWindow::wait_for_button_update_tags() {
	update_tags_button_pushed = false;
	return update_tags_button_pushed;
}

// Redraw and update text values when changing to different image view
void viewWindow::redrawUpdate() {
	// Detach previous image, name, data, and saved_tags
	detach(*img);
	detach(*name);
	detach(*data);
	detach(*changes_saved);

	// Get next image's info
	imgObj = getImage(cycleVals[index]);
	imgLoc = "images/" + to_string(imgObj.getID()) + "." + imgObj.getExtension();
	img = new Image(Point(140,150), imgLoc);

	// Crop image
	img->set_mask(Point(0,0),550,400);

	// Get image name
	name = new Text(Point(140,100), imgObj.getShortName() + "." + imgObj.getExtension());
	name->set_font_size(25);

	// Get image date and show whether it was added or downloaded
	time_t date = imgObj.getDate();

	if (imgObj.getType() == FILE_LOCAL) {
		datastring = "Added to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t " + to_string(index+1) + " / " + to_string(cycleVals.size());
	} else {
		datastring = "Downloaded to database " + to_string(asctime(gmtime(&date))) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t " + to_string(index+1) + " / " + to_string(cycleVals.size());
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

	// Redraw GUI
	Fl::redraw();
}