FROM debian:bookworm-slim

RUN apt-get update > /dev/null 2>&1 && \
    apt-get install -y build-essential > /dev/null 2>&1 && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN make

CMD ["./DropTheNumber"]