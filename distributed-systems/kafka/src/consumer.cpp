#include <iostream>
#include <string>
#include <librdkafka/rdkafka.h>

void error_callback(rd_kafka_t *rk, int err, const char *reason, void *opaque) {
    std::cerr << "Error: " << reason << std::endl;
}

void consume_messages(rd_kafka_t *rk, rd_kafka_topic_t *rkt) {
    rd_kafka_poll(rk, 0);  // Poll for new messages

    while (true) {
        rd_kafka_message_t *msg = rd_kafka_consumer_poll(rk, 1000);  // Poll for a message
        if (msg) {
            if (msg->err) {
                std::cerr << "Error: " << rd_kafka_message_errstr(msg) << std::endl;
            } else {
                std::cout << "Message consumed: " << std::string((char *)msg->payload, msg->len) << std::endl;
            }
            rd_kafka_message_destroy(msg);
        }
    }
}

int main() {
    std::string broker = "localhost:9092";
    std::string topic_name = "example_topic";
    std::string group_id = "test_group";

    rd_kafka_t *rk;  // Kafka consumer instance
    rd_kafka_conf_t *conf = rd_kafka_conf_new();  // Kafka config

    // Set error callback
    rd_kafka_conf_set_error_cb(conf, error_callback);

    // Create the Kafka consumer instance
    if (rd_kafka_conf_set(conf, "group.id", group_id.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
        std::cerr << "Error setting group.id" << std::endl;
        return -1;
    }
    if (rd_kafka_conf_set(conf, "metadata.broker.list", broker.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
        std::cerr << "Error setting metadata.broker.list" << std::endl;
        return -1;
    }

    rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, nullptr, 0);
    if (!rk) {
        std::cerr << "Failed to create Kafka consumer" << std::endl;
        return -1;
    }

    // Create topic object
    rd_kafka_topic_t *rkt = rd_kafka_topic_new(rk, topic_name.c_str(), nullptr);
    if (!rkt) {
        std::cerr << "Failed to create Kafka topic" << std::endl;
        return -1;
    }

    // Subscribe to topic
    rd_kafka_topic_partition_list_t *topics = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(topics, topic_name.c_str(), RD_KAFKA_PARTITION_UA);
    rd_kafka_subscribe(rk, topics);

    std::cout << "Consuming messages from topic: " << topic_name << std::endl;

    consume_messages(rk, rkt);  // consume messages from the topic

    // Clean up
    rd_kafka_topic_destroy(rkt);
    rd_kafka_destroy(rk);
    return 0;
}
