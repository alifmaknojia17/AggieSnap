class imageInput {
	int type = 0, id = 0;
	string loc, name, extension;
	vector<string> tag;
	public:
		int acceptInput(string, vector<string>);
		void printInfo();
		void addEntry();

		// Get functions
		string getLoc() { return loc; }
		string getName() { return name; }
		string getExtension() { return extension; }
		string getTag(int num) { return tag[(num-1)]; }
		int getID() { return id; }
		int getType() { return type; }
	private:
		bool validExtension(string);
		void setAttributes(string);
		int saveImage();
};