# Build -----------------------------------------------------

FROM ubuntu:latest as build

# creating build directory
ADD ./ /app/alert-system
WORKDIR /app/build/

ARG protobuf_version=3.11.4

RUN apt-get update && \
    apt-get install -y \
        g++ git wget tar make cmake \
# installing openssl
        openssl && \
    openssl version && \
# installing boost
    apt-get install -y \
        libboost-system-dev \
        libboost-thread-dev \
        libboost-log-dev \
        libboost-program-options-dev \
        libboost-chrono-dev \
# installing cpprestsdk and dependecies
        libcpprest-dev \
# installing protobuf (for etcd client) and dependencies
        autoconf automake libtool curl unzip \
    && \
    wget https://github.com/protocolbuffers/protobuf/releases/download/v$protobuf_version/protobuf-cpp-$protobuf_version.tar.gz && \
    tar -xzvf protobuf-cpp-$protobuf_version.tar.gz && \
    ./protobuf-cpp-$protobuf_version/configure && \
    make -C protobuf-cpp-$protobuf_version && \
    make -C protobuf-cpp-$protobuf_version check && \
    make -C protobuf-cpp-$protobuf_version install && \
    ldconfig && \
# installing grpc (for etcd client) and dependencies
    apt-get install -y build-essential && \
    git clone https://github.com/grpc/grpc.git && \
    git -git-dir=grpc/.git submodule update --init && \
    make -C grpc && \
    make -C grpc install
# building project
    protoc -I ../alert-system/third_party/etcd-cpp-apiv3/proto --grpc_out=../alert-system/third_party/etcd-cpp-apiv3/proto --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ../alert-system/third_party/etcd-cpp-apiv3/proto/rpc.proto && \
    protoc -I ../alert-system/third_party/etcd-cpp-apiv3/proto --cpp_out=../alert-system/third_party/etcd-cpp-apiv3/proto ../alert-system/third_party/etcd-cpp-apiv3/proto/*.proto && \
    cmake ../alert-system && \
#    make alert_system
    make router_example

# Run -----------------------------------------------------

FROM ubuntu:latest

# installing libcpprest library to run app
RUN apt-get update && \
    apt-get install -y \
        libcpprest \
        libboost-system-dev libboost-thread-dev libboost-log-dev \
        libboost-program-options-dev libboost-chrono-dev \
    && \
# setting user
    groupadd -r alert_system && useradd -r -g alert_system alert_system

USER alert_system

WORKDIR /app/
#COPY --from=build /app/build/alert_system .
COPY --from=build /app/build/network/server/examples/router_example/router_example .

#ENTRYPOINT ["./alert_system"]
ENTRYPOINT ["./router_example"]

