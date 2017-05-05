// Header and function definitions
#include "global.h"

// Get current value of counter
int currentCount() {
	string line;
	int count = 0;
	ifstream current("counter");
	if (current.is_open()) {
		getline(current, line);
		count = stoi(line);
		current.close();
	}
	return count;
}

// Update value of counter
void updateCount() {
	// Get current value of counter
	int count = currentCount();

	// Update value of counter
	++count;

	// Write to file
	ofstream update("counter");
	if (update.is_open()) {
		update << count << endl;
		update.close();
	}
}

// Convert a string to lowercase
string strtolower(string str) {
	for (auto i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}

// Return image object of image based on id
imageOutput getImage(int id) {
	string line;
    ifstream db("db");
    vector<string> data;
    bool found = false;
    imageOutput image;

    // If file opened successfully
    if (db) {
    	// Get each line of file
    	while (getline(db, line) && found == false) {
    		int offset = 0, pos = 0;
    		// While it keeps finding delimeters
    		while (line.find("^", offset) != string::npos) {
    			pos = line.find("^", offset);

    			// Check to see if id matches id being searched for. If not, break out of current search and look in next string
    			if (line.substr(offset, pos-offset) != to_string(id) && found == false) {
    				break;
    			}

    			// Push data between delimiters back into vector
    			data.push_back(line.substr(offset, pos-offset));
    			offset = pos+1;
    			found = true;
    		}
    	}
    }

	// If it found a match, set all the values of the image object else return a null image object
	if (found) {
		image.setAttributes(stoi(data[0]), data[1], data[2], stoi(data[3]), stoi(data[4]), vector<string> {data[5], data[6], data[7], data[8], data[9]});
	} else {
		image.setAttributes(0, "", "", 0, 0, vector<string> {"", "", "", "", ""});
	}
	return image;
}

// Return a vector of image IDs that match specified search parameters
vector<int> searchImages(string text) {
	// Init empty results vector;
	vector<int> results;

	// Don't allow empty tag searches
	if (text == "") {
		return results;
	}

	// Get all of the tags
	vector<string> tags;
	int offset = 0, pos = 0;
	
	// While it keeps finding delimeters
	while (text.find(",", offset) != string::npos) {
		pos = text.find(",", offset);

		tags.push_back(text.substr(offset, pos-offset));
		offset = pos+1;
	}
	tags.push_back(text.substr(offset, text.size()-offset));

	// Cycle through all of the images
	for (auto i = 1; i < currentCount(); ++i) {
		imageOutput check = getImage(i);

		// Cycle through all of the tags
		for (auto j = 0; j < tags.size(); ++j) {
			// If any of the tags match, push back the image id
			if (check.getTag(1) == tags[j] || check.getTag(2) == tags[j] || check.getTag(3) == tags[j] || check.getTag(4) == tags[j] || check.getTag(5) == tags[j]) {
				results.push_back(i);
			}
		}
	}

	// Remove duplicates if image contains two tags that were searched for
	vector<int>::iterator it;
	it = unique(results.begin(), results.end());
	results.resize(distance(results.begin(), it));

	return results;
}

// Default images to cycle through (all images)
vector<int> defaultImages() {
	vector<int> results;
	for (int a = 1; a < currentCount(); ++a) {
		results.push_back(a);
	}
	return results;
}

// Update the tags of specified image
void updateTags(int id, vector<string> tags) {
	stringstream data;
	for (auto i = 1; i < currentCount(); ++i) {
		imageOutput tmp = getImage(i);
		if (i == id) {
			// Update tags
			data << tmp.getID() << "^" << tmp.getName() << "^" << tmp.getExtension() << "^" << tmp.getDate() << "^" << tmp.getType() << "^" << tags[0] << "^" << tags[1] << "^" << tags[2] << "^" << tags[3] << "^" << tags[4] << "^\n";
		} else {
			// Reinput same data
			// 1^siberian_husky^jpg^1386016286^0^husky^sdaf^^^^
			data << tmp.getID() << "^" << tmp.getName() << "^" << tmp.getExtension() << "^" << tmp.getDate() << "^" << tmp.getType() << "^" << tmp.getTag(1) << "^" << tmp.getTag(2) << "^" << tmp.getTag(3) << "^" << tmp.getTag(4) << "^" << tmp.getTag(5) << "^\n";
		}
	}
	ofstream db("db");
	if (db.is_open()) {
		db << data.rdbuf();
	}
}
