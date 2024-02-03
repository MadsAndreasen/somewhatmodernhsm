FROM ubuntu:23.10

RUN apt update && apt install -y --no-install-recommends git python3-pip python-is-python3 fish clang

RUN pip install --break-system-packages meson ninja