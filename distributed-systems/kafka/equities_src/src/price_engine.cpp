#include "kafka_consumer.h"
#include <chrono>

int main(){


	KafkaConsumer kfq("localhost:9092","us-equities","equities_group");
	kfq.consume([&](std::string symbol, std::unordered_map<std::string,std::string> m){

			std::cout<<"Symbol "<<symbol<<" => ";
			for (const auto & [k,v]: m){
				std::cout<<k<<"="<<v<<" ";
			}
      auto now = std::chrono::high_resolution_clock::now();
      long now_ts=std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
		  std::cout<<"=>"<<now_ts-std::stoull(m["ts"])<<std::endl;	

	});

	return 0;
}
