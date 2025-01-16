import pika

def main():
    # Connection parameters
    connection_params = pika.ConnectionParameters('localhost')
    
    # Connect to RabbitMQ server
    connection = pika.BlockingConnection(connection_params)
    channel = connection.channel()
    
    # Declare the queue (to ensure it exists)
    queue_name = 'test_queue'
    channel.queue_declare(queue=queue_name, durable=True)

    print(f" [*] Waiting for messages in '{queue_name}'. To exit press CTRL+C")

    # Callback function to process received messages
    def callback(ch, method, properties, body):
        print(f" [x] Received: {body.decode()}")

    # Set up consumer to fetch messages from the queue
    channel.basic_consume(queue=queue_name, on_message_callback=callback, auto_ack=True)

    # Start consuming
    try:
        channel.start_consuming()
    except KeyboardInterrupt:
        print("\n [!] Exiting...")
        channel.stop_consuming()

    # Close the connection
    connection.close()

if __name__ == "__main__":
    main()
