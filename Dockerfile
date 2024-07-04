FROM debian:bookworm AS build

RUN apt-get update \
    && apt-get install -y \
        build-essential \
        cmake \
        libgtest-dev \
        clang-tidy \
    && rm -rf /var/lib/apt/lists/*

WORKDIR ${HOME}
