class imageOutput {
	int type = 0, id = 0, date = 0;
	string name, extension;
	vector<string> tag;
	public:
		void setAttributes(int, string, string, int, int, vector<string>);
		void printInfo();

		// Get functions
		string getName() { return name; }
		string getShortName();
		string getExtension() { return extension; }
		string getTag(int num) { return tag[(num-1)]; }
		int getID() { return id; }
		int getDate() { return date; }
		int getType() { return type; }
};