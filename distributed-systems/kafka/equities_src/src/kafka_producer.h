#include <iostream>
#include <string>
#include <librdkafka/rdkafka.h>
#include <thread>
#include <chrono>

class KafkaProducer {
public:
    KafkaProducer(const std::string& brokers, const std::string& topic)
        : topic(topic), producer(nullptr), conf(nullptr) {
        setup(brokers);
    }

    ~KafkaProducer() {
        if (producer) {
            rd_kafka_flush(producer, 5000); // Wait for all messages to be delivered
            rd_kafka_destroy(producer);
        }
    }

    void send(const std::string& message) {
        send_message(message);
    }

private:
    rd_kafka_t* producer;
    rd_kafka_conf_t* conf;
    std::string topic;

    void setup(const std::string& brokers) {
        char errstr[512];
        conf = rd_kafka_conf_new();

        if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(), errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
            std::cerr << "Error setting bootstrap servers: " << errstr << std::endl;
            return;
        }

        producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
        if (!producer) {
            std::cerr << "Failed to create producer: " << errstr << std::endl;
            return;
        }
    }

    void send_message(const std::string& message) {
        rd_kafka_resp_err_t err = rd_kafka_producev(
            producer,
            RD_KAFKA_V_TOPIC(topic.c_str()),
            RD_KAFKA_V_VALUE(const_cast<char*>(message.c_str()), message.size()),
            RD_KAFKA_V_END
        );

        if (err) {
            std::cerr << "Failed to produce message: " << rd_kafka_err2str(err) << std::endl;
        } else {
            std::cout << "Produced message: " << message << std::endl;
        }
        rd_kafka_flush(producer, 5000); // Wait for all messages to be delivered
    }
};

