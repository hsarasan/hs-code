# Use a minimal base image
FROM ubuntu:latest

# Set non-interactive mode to prevent prompts
ENV DEBIAN_FRONTEND=noninteractive

# Set working directory
WORKDIR /app

# Copy the compiled UDP server binary
COPY udp_server /app/udp_server

# Expose the UDP port
EXPOSE 8080/udp

# Run the UDP server
CMD ["./udp_server"]
