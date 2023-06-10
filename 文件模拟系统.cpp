// 文件模拟系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "util.h"
folder root("/", "");
util u;

int startswith(string s, string sub) {
    return s.find(sub) == 0;
}
int menu() {
    string com;
    cout << ">> ";
    //cin >> com;
    getline(cin, com);
    if (startswith(com,"quit")) {
        return 0;
    }
    vector<string> res;

    u.stringsplit(com, " ", res);
    if (startswith(com, "mkdir")) {
        if (res.size()!=3) {
            cerr << "mkdir命令需要两个参数" << endl;
            return -1;
        }
        else {
            u.mkdir(root, res[1], res[2]);
        }
    }
    if (startswith(com, "mkfile")) {
        if (res.size() != 3) {
            cerr << "mkfile命令需要两个参数" << endl;
            return -1;
        }
        else {
            u.mkfile(root, res[1], res[2]);
        }
    }
    if (startswith(com, "write")) {
        if (res.size() != 3) {
            cerr << "write命令需要两个参数" << endl;
            return -1;
        }
        else {
            u.write(root, res[1], res[2]);
        }
    }
    if (startswith(com, "show")) {
        if (res.size() != 2) {
            cerr << "show命令需要一个参数" << endl;
            return -1;
        }
        else {
            u.show(root, res[1]);
        }
    }

    if (startswith(com, "copy")) {
        if (res.size() != 3) {
            cerr << "copy命令需要两个参数" << endl;
            return -1;
        }
        else {
            u.copy(root, res[1], res[2]);
        }
    }

    if (startswith(com, "del")) {
        if (res.size() != 2) {
            cerr << "write命令需要一个参数" << endl;
            return -1;
        }
        else {
            u.del(root, res[1]);
        }
    }

    if (startswith(com, "ls")) {
        if (res.size() != 2) {
            cerr << "ls命令需要一个参数" << endl;
            return -1;
        }
        else {
            u.ls(root, res[1]);
        }
    }

    if (startswith(com, "help")) {
        if (res.size() == 2) {
            u.help(res[1]);
        }
        else {
            u.help("");
        }
    }
}

int main()
{
    //
    //folder now = root;

    //u.mkfile(root, "/","new_file_name");
    ////u.mkfile(root, "/name", "new_file_name");
    //u.ls(root);
    //u.mkdir(root, "/", "name1");
    //u.mkfile(root, "/name1", "new_file_name1");

    //u.ls(root);
    //u.ls(root.getFolderChild()["name1"]);

    //u.mkdir(root, "/name1/", "name1");
    //u.ls(root.getFolderChild()["name1"]);

    //u.ls(root.getFolderChild()["name1"].getFolderChild()["name1"]);

    //u.ls(root,"/name1");

    //u.write(root, "/new_file_name","adadadaa");

    //u.show(root, "/new_file_name");
    //u.copy(root, "/name1/new_file_name1", "/new_file_name1");
    //
    //u.ls(root);

    //u.del(root, "/new_file_name1");
    //u.ls(root);

    //u.help("MKdir");
    cout << "\t\t" << "一个简单模拟文件系统的小程序\t\t\t周景鑫" << endl;
    while (menu() != 0);

}