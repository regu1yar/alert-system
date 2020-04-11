# Build -----------------------------------------------------

FROM ubuntu:latest as build

# creating build directory
ADD ./ /app/alert-system
WORKDIR /app/build/

RUN apt-get update && \
    apt-get install -y \
        g++ wget tar make cmake \
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
# installing cpprestsdk and requirements
        libcpprest-dev \
    && \
# building project
    cmake ../alert-system && \
    make alert_system
#    make router_example

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
COPY --from=build /app/build/alert_system .
#COPY --from=build /app/build/network/server/examples/router_example/router_example .

ENTRYPOINT ["./alert_system"]
#ENTRYPOINT ["./router_example"]
