#pragma once
#include <iostream>
using namespace std;
class File
{
private:
	string name;
	string content;
	string path;

public:
	File(string p = "/", string n = "new_file", string c = ""):name(n),path(p),content(c) {

	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	string getContent() {
		return content;
	}

	void setContent(string content) {
		this->content = content;
	}

	string getPath() {
		return path;
	}

	void setPath(string path) {
		this->path = path;
	}


};

