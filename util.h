#pragma once
#include "head.h"
#include <string>
#include <algorithm>

using namespace std;

class util
{
public:
	string errorfile = "�޷��ҵ��ļ�:\t";
	string errorfolder = "�޷��ҵ��ļ���:\t";
	void stringsplit(string& str, string split, vector<string>& res) {
		string::size_type pos1, pos2;
		size_t len = str.length();
		pos2 = str.find(split);
		pos1 = 0;
		while (string::npos != pos2) {
			string add = str.substr(pos1, pos2 - pos1);
			if (add != "") {
				res.emplace_back(add);
			}
			

			pos1 = pos2 + split.size();
			pos2 = str.find(split, pos1);
		}
		if (pos1 != len)
			res.emplace_back(str.substr(pos1));
	}

	int path2file(folder& root, string path, File*& out) {
		vector<string> res;
		stringsplit(path, "/", res);

		folder* f = &root;
		for (int i = 0; i < res.size()-1; i++) {
			if (!f->getFolderChild(res[i], f)) {
				cerr << errorfolder << res[i] << endl;
				return false;
			}
		}

		if (f->fileChild.find(res[res.size()-1]) != f->fileChild.end())
		{
			out = &(f->fileChild[res[res.size() - 1]]);
			return true;
		}
		else {
			cerr << errorfile << res[res.size() - 1] << endl;
		}
		return false;
	}

	int path2folder(folder& root, string path, folder*& out) {
		vector<string> res;
		stringsplit(path, "/", res);
		if (res.size() == 0) {
			out = &root;
			return true;
		}
		folder* f = &root;
		for (int i = 0; i < res.size()-1; i++) {
			if (!f->getFolderChild(res[i], f)) {
				cerr << errorfolder << res[i] << endl;
				return false;
			}
		}
		//auto filec = f->getFolderChild();
		
		if (f->folderChild.find(res[res.size() - 1]) != f->folderChild.end())
		{
			out = &(f->folderChild[res[res.size() - 1]]);
			return true;
		}
		else {
			cerr << errorfolder << res[res.size() - 1] << endl;
			return false;
		}

	}
public:
	map<string, string> helpmap;
	util() {
		helpmap["mkfile"] = "�ļ��������� ��ʽΪ:mkfile Ҫ�������ļ�����·�� �ļ���";
		helpmap["mkdir"] = "�ļ��д������� ��ʽΪ:mkdir Ҫ�������ļ��еľ���·�� �ļ�����";
		helpmap["write"] = "���ļ�д���������� ��ʽΪ:write �ļ�����·�� Ҫд����ַ���";
		helpmap["show"] = "��ȡ�ļ����� ��ʽΪ:show Ҫ��ȡ���ļ�����·��";
		helpmap["copy"] = "�ļ��������� ��ʽΪ:copy Ҫ���Ƶ��ļ�����·�� ���Ƶ��ľ���·��";
		helpmap["del"] = "�ļ�ɾ������ ��ʽΪ:del Ҫɾ�����ļ�����·��";
		helpmap["ls"] = "�г�Ŀ¼�����ļ� ��ʽΪ:ls Ҫ�鿴���ļ��о���·��";
		helpmap["help"] = "�������� ��ʽΪ:help��help����Ҫ������";
		helpmap[""] = "\
			�����:\n\
			1. �ļ����� mkfile\n\
			2. �ļ��д��� mkdir\n\
			3. д���ļ� write\n\
			4. ��ʾ�ļ����� show\n\
			5. �����ļ� copy\n\
			6. ɾ���ļ� del\n\
			7. �г�Ŀ¼�����ļ� ls\n\
			8. ���� help\n\
			9. �˳� quit\n\
			����help����������ϸ����\
			";
	}
	int mkfile(folder& root, string path, string newFileName) {
		vector<string> res;
		stringsplit(path, "/", res);

		folder *f = &root;
		for (int i = 0; i < res.size(); i++) {
			if (!f->getFolderChild(res[i], f)) {
				
				cerr << errorfolder << res[i] << endl;
				return false;
			}
		}

		return f->addFileChild(path, newFileName);
	}

	int mkfile(folder& f, string newFileName) {
		return f.addFileChild(f.getPath(), newFileName);
	}

	int mkdir(folder& root, string path, string newFolderName) {
		vector<string> res;
		stringsplit(path, "/", res);

		folder *f = &root;
		for (int i = 0; i < res.size(); i++) {
			if (!root.getFolderChild(res[i], f)) {
				cerr << errorfolder << res[i] << endl;
				return false;
			}
		}
		return f->addFolderChild(path+newFolderName, newFolderName);
	}

	int mkdir(folder& f, string newFolderName) {
		return f.addFolderChild(f.getPath(), newFolderName);
	}

	void ls(folder& f) {
		int filenum = 0,foldernum = 0;
		for (int i = 0; i < 8; i++) {
			cout << "-";
		}
		cout << "  " << f.getPath() << "  �е��ļ��嵥:";
		cout << endl;
		for (auto [k,v] : f.getFileChild()) {
			filenum += 1;
			cout << "�ļ�:\t" << k << endl;
		}

		for (auto [k,v]: f.getFolderChild()) {
			foldernum += 1;
			cout << "�ļ���:\t" << k << endl;
		}
		cout << "�����ļ�:" << filenum << "��" << endl;
		cout << "�����ļ���:" << foldernum << "��" << endl;
		for (int i = 0; i < 20;i++) {
			cout << "-";
		}
		cout << endl;
		
	}

	void ls(folder root, string path) {
		folder *f;
		if (path2folder(root, path, f)) {
			ls(*f);
		}
	}

	int write(folder& root, string path, string content) {
		File *ff;
		if (path2file(root, path, ff))
		{
			ff->setContent(content);
			return true;
		}
		return false;
	}

	int show(folder& root, string path) {
		File *ff;
		if (path2file(root, path, ff))
		{
			cout << path << "�ļ�����Ϊ:\t"<<ff->getContent() << endl;
			return true;
		}
		return false;
	}

	int copy(folder& root,string from, string to) {
		File* ff;
		if (!path2file(root, from, ff)) {
			cerr << "���ļ�" << from << "ʧ��" << endl;
			return false;
		}
		File* fto;
		vector<string> res;
		stringsplit(to, "/", res);
		mkfile(root,to.substr(0, to.size()-res[res.size()-1].size()), res[res.size()-1]);
		if (!path2file(root, to, fto)) {
			cerr << "�����ļ�" << to << "ʧ��" << endl;
			return false;
		}
		fto->setContent(ff->getContent());
		return true;
	}

	int del(folder& root, string path) {
		folder *out;
		vector<string> res;
		stringsplit(path, "/", res);
		string rp = path.substr(0, path.size() - res[res.size() - 1].size());
		// cout << rp << " rp " << endl;
		if (!path2folder(root, rp, out)) {
			cerr << "�ļ�ɾ��ʧ��" << path << endl;
			return false;
		}
		out->fileChild.erase(res[res.size() - 1]);
		return true;
	}
	
	void help(string command) {
		transform(command.begin(), command.end(), command.begin(), ::tolower);

		cout << command << "\t" << helpmap[command] << endl;
	}
};
