FROM ubuntu:18.04 AS build

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    && rm -rf /var /lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN cmake . && make

FROM ubuntu:18.04

COPY --from=build /app/worker-2 /app/worker-2

CMD ["/app/worker-2"]