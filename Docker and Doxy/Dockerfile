FROM ubuntu:22.04
RUN apt-get update && apt-get install -y \
    build-essential \
    qt6-base-dev \
    qt6-declarative-dev \
    libgl1-mesa-dev \
    cmake \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . /app
RUN mkdir -p build_server && \
cd build_server && \
qmake6 ../Tech_prog_server.pro && \
make
ENTRYPOINT ["sh", "-c"]
CMD ["./build_server/Tech_prog_server"]
