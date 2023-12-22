FROM ubuntu:18.04 AS build

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libssl-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Download and install Boost
RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.72.0/source/boost_1_72_0.tar.gz \
    && tar -xf boost_1_72_0.tar.gz \
    && cd boost_1_72_0 \
    && ./bootstrap.sh \
    && ./b2 install

WORKDIR /app

# Copy your application files
COPY . /app

# Build the application
RUN cmake . && make

# Final stage
FROM ubuntu:18.04

# Copy the binaries from the build stage
COPY --from=build /app/master /app/master

CMD ["/app/master"]
