FROM ubuntu:23.04

RUN apt update && apt install -y --no-install-recommends python3 build-essential ninja-build meson git