#include "global.h"

// Set all of the values of the imageOutput object
void imageOutput::setAttributes(int id, string name, string ext, int date, int type, vector<string> tag) {
	this->id = id;
	this->name = name;
	this->extension = ext;
	this->date = date;
	this->type = type;
	this->tag = tag;

}

// Print image info
void imageOutput::printInfo() {
	cout << "------" << endl;
	cout << "id:\t\t" << getID() << endl;
	cout << "name:\t\t" << getName() << endl;
	cout << "Extension:\t" << getExtension() << endl;
	cout << "date:\t\t" << getDate() << endl;
	cout << "tag 1:\t\t" << getTag(1) << endl;
	cout << "tag 2:\t\t" << getTag(2) << endl;
	cout << "tag 3:\t\t" << getTag(3) << endl;
	cout << "tag 4:\t\t" << getTag(4) << endl;
	cout << "tag 5:\t\t" << getTag(5) << endl;
	cout << "------" << endl;
}

string imageOutput::getShortName() {
	if (this->getName().length() > 35) {
		return this->getName().substr(0, 35) + "...";
	}
	return this->getName();
}