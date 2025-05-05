#include "kafka_consumer.h"


int main(){


	KafkaConsumer kfq("localhost:9092","us-equities","equities_group");
	kfq.consume([&](std::string symbol, std::unordered_map<std::string,std::string> m){

			std::cout<<"Symbol "<<symbol<<" => ";
			for (const auto & [k,v]: m){
				std::cout<<k<<"="<<v<<" ";
			}
			std::cout<<std::endl;

	});

	return 0;
}
