#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "File.h"


using namespace std;
class folder
{
public:
	map<string, File> fileChild;
	map<string, folder> folderChild;
private:
	
	
	string path;
	string name;

public:
	folder(string p = "/", string n = "") :name(n), path(p){

	}
	int addFileChild(string path, string name) {
		auto k = name;
		if (fileChild.find(k) == fileChild.end()) {
			fileChild[k] = *new File(path, name);
			return true;
		}
		cerr << "has same file:\t" << k << endl;
		return false;
	}

	int addFolderChild(string p, string f) {
		string k = f;
		if (folderChild.find(k) == folderChild.end()) {
			folderChild[k] = folder(p,f);
			return true;
		}
		return false;
	}

	string getName() {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	string getPath() {
		return path;
	}

	void setPath(string path) {
		this->path = path;
	}

	int getFolderChild(string name, folder*& out) {
		if (folderChild.find(name) != folderChild.end()) {
			out = &folderChild[name];
			return true;
		}
		return false;
	}

	map<string, File>& getFileChild() {
		return fileChild;
	}

	map<string, folder>& getFolderChild() {
		return folderChild;
	}
};

