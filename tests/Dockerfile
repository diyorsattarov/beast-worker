FROM ubuntu:18.04 AS build

# Install dependencies
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libssl-dev \
    wget \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app

# Copy your application files
COPY . /app

# Build the application
RUN cmake . && make

# Final stage
FROM ubuntu:18.04

# Copy the binaries from the build stage
COPY --from=build /app/tests /app/tests

CMD ["/app/tests"]
