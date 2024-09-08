#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct FileSystemItem{
    virtual void showDetails() const=0;
};
struct File: public FileSystemItem {
    string name;
    File(const string name_):name(name_){}
    void showDetails() const{
        cout<<"This is file "<<name<<std::endl;
    }
};
struct Directory : public FileSystemItem{
    string name;
    vector<FileSystemItem*> collection;
    Directory(const string name_):name(name_){}
    void showDetails() const{
        cout<<"Directory => "<<name<<std::endl;
        for (const auto  item: collection)
            item->showDetails();
    }
};

int main(){
  Directory root_dir("/");
  Directory child_dir("etc");
  File fs1("password");
  File fs2("users");
  child_dir.collection.push_back(&fs1);
  child_dir.collection.push_back(&fs2);
  root_dir.collection.push_back(&child_dir);

  root_dir.showDetails();

  return 0;
}