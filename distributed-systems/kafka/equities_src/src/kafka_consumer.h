#include <iostream>
#include <string>
#include <librdkafka/rdkafka.h>

class KafkaConsumer {
public:
    KafkaConsumer() {
        std::string broker = "localhost:9092";
        std::string topic_name = "us-equities";
        std::string group_id = "test_group";

        // Create Kafka config and set error callback
        conf = rd_kafka_conf_new();
        rd_kafka_conf_set_error_cb(conf, error_callback);

        // Set configuration properties
        if (rd_kafka_conf_set(conf, "group.id", group_id.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
            std::cerr << "Error setting group.id" << std::endl;
            return;
        }
        if (rd_kafka_conf_set(conf, "metadata.broker.list", broker.c_str(), nullptr, 0) != RD_KAFKA_CONF_OK) {
            std::cerr << "Error setting metadata.broker.list" << std::endl;
            return;
        }

        // Create Kafka consumer instance
        rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, nullptr, 0);
        if (!rk) {
            std::cerr << "Failed to create Kafka consumer" << std::endl;
            return;
        }

        // Create topic partition list and subscribe
        rd_kafka_topic_partition_list_t *topics = rd_kafka_topic_partition_list_new(1);
        rd_kafka_topic_partition_list_add(topics, topic_name.c_str(), RD_KAFKA_PARTITION_UA);
        if (rd_kafka_subscribe(rk, topics) != RD_KAFKA_RESP_ERR_NO_ERROR) {
            std::cerr << "Failed to subscribe to topic" << std::endl;
            return;
        }
    }

    void consume() {
        while (true) {
            // Poll for new messages
            rd_kafka_message_t *msg = rd_kafka_consumer_poll(rk, 1000);  // Poll with timeout
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

    ~KafkaConsumer() {
        rd_kafka_unsubscribe(rk);  // Unsubscribe from the topic
        rd_kafka_destroy(rk);      // Destroy the Kafka consumer instance
    }

private:
    static void error_callback(rd_kafka_t *rk, int err, const char *reason, void *opaque) {
        std::cerr << "Error: " << reason << std::endl;
    }

    rd_kafka_t *rk;             // Kafka consumer instance
    rd_kafka_conf_t *conf;      // Kafka config
};

