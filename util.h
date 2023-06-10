#pragma once
#include "head.h"
#include <string>
#include <algorithm>

using namespace std;

class util
{
public:
	string errorfile = "无法找到文件:\t";
	string errorfolder = "无法找到文件夹:\t";
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
		helpmap["mkfile"] = "文件创建命令 格式为:mkfile 要创建的文件绝对路径 文件名";
		helpmap["mkdir"] = "文件夹创建命令 格式为:mkdir 要创建的文件夹的绝对路径 文件夹名";
		helpmap["write"] = "向文件写入数据命令 格式为:write 文件绝对路径 要写入的字符串";
		helpmap["show"] = "读取文件命令 格式为:show 要读取的文件绝对路径";
		helpmap["copy"] = "文件复制命令 格式为:copy 要复制的文件绝对路径 复制到的绝对路径";
		helpmap["del"] = "文件删除命令 格式为:del 要删除的文件绝对路径";
		helpmap["ls"] = "列出目录所有文件 格式为:ls 要查看的文件夹绝对路径";
		helpmap["help"] = "帮助命令 格式为:help或help加需要的命令";
		helpmap[""] = "\
			命令共有:\n\
			1. 文件创建 mkfile\n\
			2. 文件夹创建 mkdir\n\
			3. 写入文件 write\n\
			4. 显示文件内容 show\n\
			5. 复制文件 copy\n\
			6. 删除文件 del\n\
			7. 列出目录所有文件 ls\n\
			8. 帮助 help\n\
			9. 退出 quit\n\
			输入help加命令有详细帮助\
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
		cout << "  " << f.getPath() << "  中的文件清单:";
		cout << endl;
		for (auto [k,v] : f.getFileChild()) {
			filenum += 1;
			cout << "文件:\t" << k << endl;
		}

		for (auto [k,v]: f.getFolderChild()) {
			foldernum += 1;
			cout << "文件夹:\t" << k << endl;
		}
		cout << "共有文件:" << filenum << "个" << endl;
		cout << "共有文件夹:" << foldernum << "个" << endl;
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
			cout << path << "文件内容为:\t"<<ff->getContent() << endl;
			return true;
		}
		return false;
	}

	int copy(folder& root,string from, string to) {
		File* ff;
		if (!path2file(root, from, ff)) {
			cerr << "打开文件" << from << "失败" << endl;
			return false;
		}
		File* fto;
		vector<string> res;
		stringsplit(to, "/", res);
		mkfile(root,to.substr(0, to.size()-res[res.size()-1].size()), res[res.size()-1]);
		if (!path2file(root, to, fto)) {
			cerr << "创建文件" << to << "失败" << endl;
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
			cerr << "文件删除失败" << path << endl;
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

