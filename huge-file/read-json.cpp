#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>

int count=0;
std::map<std::string, std::string> data_map;

int countSubstring(const std::string& str, const std::string& sub)
{
	if (sub.length() == 0) return 0;
	int count = 0;
	for (size_t offset = str.find(sub); offset != std::string::npos;
	offset = str.find(sub, offset + sub.length()))
	{
		++count;
	}
	return count;
} 

void extract(std::string & str, int pos){
    int vm_pos = str.find("VM", pos);
    int length_to_look = vm_pos - pos;
    //assert(length_to_look<6000);
    std::string full_data = str.substr(pos,length_to_look);
    int start_pos=0;
    int valor_count = countSubstring(full_data, "valor");
    //std::cout<<valor_count<<std::endl;
    //assert(valor_count<50);
    for (int i=0;i<valor_count;++i) {
        int data_pos=full_data.find("data",start_pos);
        data_pos+=7;
        int valor_pos=full_data.find("valor",start_pos);
        valor_pos+=7;
        auto date_and_time = full_data.substr(data_pos,16);
        auto valor_end = full_data.find(',',valor_pos);
        auto valor_length = valor_end-valor_pos;
        auto valor = full_data.substr(valor_pos,valor_length);
        data_map[date_and_time]=valor;
        start_pos = valor_pos+1;
    }
}

void printToFile(const std::string & filename){
    std::ofstream ofs(filename.c_str());
    for (const auto & [k,v]: data_map){
        ofs<<k<<","<<v<<std::endl;
    }
}

int main(int argc, char * argv[]){

    if (argc!=3){
        std::cout<<"Usage: "<<argv[0]<<" <input file> <output file>"<<std::endl;
        std::cout<<"Example : ./extract /home/user/beena/2021.json /home/user/beena/2021.out"<<std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    std::string file_content;
    std::getline(input_file, file_content);
    std::cout<<"Size Of File = "<<file_content.size()<<std::endl;
    int pos {0};
    bool done{false};

    while(!done){
        auto ret = file_content.find("VK",pos+1);
        if (ret==std::string::npos) break;
        pos = ret;
        extract(file_content,pos);
        count++;
    }
    printToFile(argv[2]);
    assert(count==365);
    
    return 0;
}