
#include <iostream>
#include <librdkafka/rdkafka.h>
#include <thread>
#include <chrono>

// Kafka Producer
void produce_messages(const std::string& brokers, const std::string& topic, int num_messages, int delay_ms) {
    rd_kafka_t* producer;
    rd_kafka_conf_t* conf = rd_kafka_conf_new();

    char errstr[512];

    // Set the bootstrap servers
    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers.c_str(), errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        std::cerr << "Error setting bootstrap servers: " << errstr << std::endl;
        return;
    }

    // Create the producer instance
    producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (!producer) {
        std::cerr << "Failed to create producer: " << errstr << std::endl;
        return;
    }

    for (int i = 0; i < num_messages; ++i) {
        std::string message = "Message " + std::to_string(i + 1);

        rd_kafka_resp_err_t err = rd_kafka_producev(
            producer,
            RD_KAFKA_V_TOPIC(topic.c_str()),
						RD_KAFKA_V_VALUE(const_cast<void*>(static_cast<const void*>(message.c_str())), message.size()),
            RD_KAFKA_V_END
        );

        if (err) {
            std::cerr << "Failed to produce message: " << rd_kafka_err2str(err) << std::endl;
        } else {
            std::cout << "Produced message: " << message << std::endl;
        }

        // Flush and wait before sending the next message
        rd_kafka_flush(producer, 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }

    // Wait for all messages to be delivered
    rd_kafka_flush(producer, 5000);

    // Destroy the producer instance
    rd_kafka_destroy(producer);
}

int main() {
    std::string brokers = "localhost:9092";
    std::string topic = "example_topic";

    int num_messages = 10; // Number of messages to produce
    int delay_ms = 1000;   // Delay in milliseconds between messages

    // Produce messages in a loop
    produce_messages(brokers, topic, num_messages, delay_ms);

    return 0;
}



