# Build -----------------------------------------------------

FROM gcc:latest as build

RUN apt-get update && \
    apt-get install -y \
        wget tar make \
    && \
# installing openssl
    apt-get -y install openssl && \
    openssl version

# installing cmake from sources (version 3.13+ required)
ARG cmake_version=3.17
ARG cmake_build=1
WORKDIR /cmake_build
RUN wget https://cmake.org/files/v$cmake_version/cmake-$cmake_version.$cmake_build.tar.gz && \
    tar -xzvf cmake-$cmake_version.$cmake_build.tar.gz && \
    ./cmake-$cmake_version.$cmake_build/bootstrap && \
    make -j4 && \
    make install && \
    cmake --version

# installing boost
RUN apt-get install -y \
        libboost-system-dev \
        libboost-thread-dev \
        libboost-log-dev \
        libboost-program-options-dev \
        libboost-chrono-dev

# installing cpprestsdk and requirements
RUN apt-get install -y libcpprest-dev

# building project
ADD ./ /app/alert-system
WORKDIR /app/build
RUN cmake ../alert-system && \
    make

ENTRYPOINT ["./app/build/router_example"]

# Run -----------------------------------------------------

FROM ubuntu:latest

#RUN groupadd -r alert_system && useradd -r -g alert_system alert_system
#USER alert_system

WORKDIR /app
COPY --from=build /app/build/router_example .

ENTRYPOINT ["./router_example"]
