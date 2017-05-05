// Header and function definitions
#include "global.h"

// Asks the user for an input file and accept it if extension is valid.
int imageInput::acceptInput(string loc, vector<string> tag) {
	// No error so far
	int error = 0;

	// Copy location and tags from parameter to object's location
	this->loc = loc;
	this->tag = tag;

	// Determines if file is a local file or a URL
	if ((loc.substr(0, 7) == "http://" || loc.substr(0, 8) == "https://") || loc.substr(0, 4) == "www.") {
		type = FILE_URL;
	} else {
		// Local file
		type = FILE_LOCAL;
	}

	// Invalid extension
	if (!validExtension(loc)) {
		return 1;
	}

	// Set the value of the imageInput's name and extension
	setAttributes(loc);

	// Download / copy file from URL or local
	error = saveImage();

	// If there was an error while copying / downloading image
	if (error != 0) {
		return error;
	}

	// Input new entry into image database
	addEntry();

	return 0;
}

// Print image info
void imageInput::printInfo() {
	cout << "------\nlocation:\t" << loc << "\nname:\t" << name << "\nextension:\t" << extension << "\ntype:\t" << type << "\n------" << endl;
}

// Add image to database
void imageInput::addEntry() {
	// Update value of counter
	ofstream db("db", ios::app);
	if (db.is_open()) {
		// 1^siberian_husky^jpg^1386016286^0^husky^sdaf^^^^
		db << getID() << "^" << getName() << "^" << getExtension() << "^" << time(0)-(3600*6) << "^" << getType() << "^" << strtolower(getTag(1)) << "^" << strtolower(getTag(2)) << "^" << strtolower(getTag(3)) << "^" << strtolower(getTag(4)) << "^" << strtolower(getTag(5)) << "^\n";
	}
}

// Checks the file for a valid extension and also updates value of object's extension
bool imageInput::validExtension(string file) {
	int pos = 1;
	string section, ext;
	vector <string>exts = {"jpg", "gif", "jpeg", "bm", "bmp", "pbm", "pgm", "png", "ppm", "xbm", "xpm"};

	// Step back character by charcter till period is detected to get extension
	while (1) {
		try {
			section = file.substr(file.length()-pos, pos);

			// Record filename's extension
			if (section.substr(0, 1) == ".") {
				ext = section.substr(1, section.length() - 1);
				break;
			}
			pos++;
		} catch (exception &e) {
			return 0;
		}
	}

	// Check if valid extension, uppercase/lowercase
	for (int i = 0; i < exts.size(); ++i) {
		if (strtolower(ext) == exts[i]) {
			return 1;
		}
	}
	return 0;
}

// Sets the values of the imageInput's name and extension
void imageInput::setAttributes(string file) {
	// Init. vars
	int pos = 1;
	string section, ext, name;
	bool ext_found = false;

	// Step backwards one character at a time until reach the first period.
	while (1) {
		try {
			section = file.substr(file.length()-pos, pos);

			// Record filename's extension
			if (section.substr(0, 1) == "." && ext_found == false) {
				ext = strtolower(section.substr(1, section.length() - 1));

				// Set imageInput's extension
				this->extension = ext;

				// Update flag for extension found
				ext_found = true;
			}

			// Record filename
			if (section.substr(0, 1) == "/" || pos == file.length()) {
				if (getType() == FILE_URL) {
					name = section.substr(1, section.length()-ext.length()-2);
				} else {
					name = section.substr(0, section.length()-ext.length()-1);
				}

				// Remove 1st character if slash
				if (name[0] == '/') {
					name = name.substr(1, name.length()-1);
				}

				// Set imageInput's name
				this->name = name;
				break;
			}

			// Increment position if period not found
			pos++;
		} catch (exception &e) {
			cerr << e.what() << endl;
			exit (EXIT_FAILURE);
		}
	}

	// Set image ID
	id = currentCount();
}

// Save the image
int imageInput::saveImage() {
	string command;
	int error = 0;

	// If imageInput is a URL, download from internet
	if (getType() == FILE_URL) {
		// Bypass 403 forbidden and misc. by faking self as browser.
		command = "wget -U 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.8.1.6) Gecko/20070802 SeaMonkey/1.1.4' --no-check-certificate " + getLoc() + " -O images/" + to_string(getID()) + "." + getExtension() + " >/dev/null 2>&1";
	} else  {
		// Or else, copy local file
		command = "cp " + getLoc() +  " images/" + to_string(getID()) + "." + getExtension() + " >/dev/null 2>&1";
	}

	// Execute command
	error = system(command.c_str());

	// Error downloading from URL
	if (error != 0 && getType() == FILE_URL) {
		// Remove file that is downloaded since it is invalid
		command = "rm images/" + to_string(getID()) + "." + getExtension();
		system(command.c_str());

		return 2;
	}

	// Error copying local file
	if (error != 0 && getType() == FILE_LOCAL) {
		return 3;
	}

	// Update counter
	updateCount();

	return 0;
}